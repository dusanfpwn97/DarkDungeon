// Copyright (C) Pakyman Prod. 2020. All Rights Reserved.


#include "Components/ACFEffectsDispatcherComponent.h"
#include "Actors/ACFCharacter.h"
#include <Kismet/GameplayStatics.h>
#include "Game/ACFData.h"
#include <Sound/SoundBase.h>
#include <Sound/SoundCue.h>

// Sets default values for this component's properties
UACFEffectsDispatcherComponent::UACFEffectsDispatcherComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UACFEffectsDispatcherComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

void UACFEffectsDispatcherComponent::ClientsPlayEffect_Implementation(const FEffect& effect, class AACFCharacter* instigator)
{
	Internal_PlayEffect(instigator, effect);
}

bool UACFEffectsDispatcherComponent::ClientsPlayEffect_Validate(const FEffect& effect, class AACFCharacter* instigator)
{
	return true;
}

void UACFEffectsDispatcherComponent::ServerPlayReplicatedEffect_Implementation(const FEffect& effect, class AACFCharacter* instigator)
{
	if (instigator)
	{
		instigator->MakeNoise(effect.NoiseEmitted, instigator, instigator->GetActorLocation(), effect.NoiseEmitted );
		ClientsPlayEffect(effect, instigator);
	}
}

bool UACFEffectsDispatcherComponent::ServerPlayReplicatedEffect_Validate(const FEffect& effect, class AACFCharacter* instigator)
{
	return true;
}

void UACFEffectsDispatcherComponent::PlayEffectLocally(const FEffect& effect, class AACFCharacter* instigator)
{
	Internal_PlayEffect(instigator, effect);
}

void UACFEffectsDispatcherComponent::Internal_PlayEffect(class AACFCharacter* instigator, const FEffect& effect)
{
	if (instigator)
	{

		switch (effect.SpawnLocation)
		{
		case ESpawnFXLocation::ESpawnOnActorLocation:
		case ESpawnFXLocation::ESpawnAttachedToSocketOrBone:
			SpawnSoundAndParticleAttached(effect, instigator);
			break;
		case ESpawnFXLocation::ELastDamageLocation:
			SpawnSoundAndParticleAtLocation(effect, instigator->GetLastDamageInfo().hitResult.Location);
			break;
		default:
			SpawnSoundAndParticleAttached(effect, instigator);
			break;
		}
	}
}

void UACFEffectsDispatcherComponent::SpawnSoundAndParticleAttached(const FEffect& effect, class AACFCharacter* instigator)
{
	if (effect.ActionParticle)	{
		UGameplayStatics::SpawnEmitterAttached(effect.ActionParticle, instigator->GetMesh(), effect.SocktOrBoneName);
	}
	
	if (effect.ActionSound){
		UGameplayStatics::SpawnSoundAttached(effect.ActionSound, instigator->GetMesh(), effect.SocktOrBoneName);
	}
}

void UACFEffectsDispatcherComponent::SpawnSoundAndParticleAtLocation(const FEffect& effect, const FVector& location)
{
	if (effect.ActionParticle)	{
		UGameplayStatics::SpawnEmitterAtLocation(this, effect.ActionParticle, location);
	}
	
	if (effect.ActionSound)	{
		UGameplayStatics::SpawnSoundAtLocation(this, effect.ActionSound, location);
	}
}

