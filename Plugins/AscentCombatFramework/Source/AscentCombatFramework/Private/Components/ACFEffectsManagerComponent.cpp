// Copyright (C) Pakyman Prod. 2020. All Rights Reserved.

#include "Components/ACFEffectsManagerComponent.h"
#include <CollisionQueryParams.h>
#include "Actors/ACFCharacter.h"
#include <PhysicalMaterials/PhysicalMaterial.h>
#include "Game/ACFFunctionLibrary.h"
#include "Components/ACFDamageHandlerComponent.h"

// Sets default values for this component's properties
UACFEffectsManagerComponent::UACFEffectsManagerComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

	DamageEffectsByHitReaction.Add(UACFFunctionLibrary::GetDefaultHitState(), FEffectByDamageType());
}


// Called when the game starts
void UACFEffectsManagerComponent::BeginPlay()
{
	Super::BeginPlay();

	CharacterOwner = Cast<AACFCharacter>(GetOwner());

	UACFDamageHandlerComponent* DamageHanlder = GetOwner()->FindComponentByClass<UACFDamageHandlerComponent>();

	if (DamageHanlder) {
		DamageHanlder->OnDamageReceived.AddDynamic(this, &UACFEffectsManagerComponent::HandleDamageReceived);
	}
}


void UACFEffectsManagerComponent::TriggerFootstepFX(FName footBone /*= NAME_None*/)
{
	FEffect fxToPlay;
	if (bCheckForSurface)
	{
		FEffect* fx = FootstepEffectsBySurface.Find(GetCurrentTerrain());
		if (!fx)
		{
			return;
		}
		else
		{
			fxToPlay = *fx;
		}
	}
	else
	{
		fxToPlay = DefaultFootstepFX;
	}

	FVector ownerLocation; 

	if (footBone != NAME_None) {
		fxToPlay.SocktOrBoneName = footBone;
		ownerLocation = CharacterOwner->GetMesh()->GetSocketLocation(footBone);
	}
	else	{
		ownerLocation = CharacterOwner->GetActorLocation();
	}
	
	UACFLocomotionComponent* locComp = CharacterOwner->GetLocomotionComponent();

	if (locComp)
	{
		float *noise = FootstepNoiseByLocomotionState.Find(locComp->GetCurrentLocomotionState());
		if (noise)
		{
			fxToPlay.NoiseEmitted = *noise;
		}			
	}

	UACFFunctionLibrary::PlayActionEffect(fxToPlay, CharacterOwner, this);

/*	UACFFunctionLibrary::PlayImpactEffect(FootstepImpact, ownerLocation, CharacterOwner, this);*/
}


EPhysicalSurface UACFEffectsManagerComponent::GetCurrentTerrain() 
{
	ensure(CharacterOwner);
	if (CharacterOwner)
	{
		FCollisionQueryParams RV_TraceParams = FCollisionQueryParams(FName(TEXT("Trace")), true, CharacterOwner);

		RV_TraceParams.bTraceComplex = true;
		RV_TraceParams.bReturnPhysicalMaterial = true;

		FName bone = FName("");

		FVector Start = CharacterOwner->GetActorLocation();
		FVector End = Start + (FVector(0, 0, 1)*TraceLengthByActorLocation*-1);

		//Re-initialize hit info
		FHitResult RV_Hit(ForceInit);

		bool bHit = GetWorld()->LineTraceSingleByObjectType(
			RV_Hit,					//result
			Start,					//start
			End,					//end
			ECC_WorldStatic,		//collision channel
			RV_TraceParams);

		if (bHit) {
			UE_LOG(LogTemp, Warning, TEXT("Actro hitted: %s"), *RV_Hit.Actor->GetName());
			UPhysicalMaterial* PhysicsMtl = RV_Hit.PhysMaterial.Get();
			EPhysicalSurface surface = PhysicsMtl->SurfaceType;
			return surface;
		}
	}

	return EPhysicalSurface::SurfaceType_Max;
}

void UACFEffectsManagerComponent::HandleDamageReceived(const FACFDamageEvent& damageEvent)
{
	OnDamageImpactReceived(damageEvent);
}

void UACFEffectsManagerComponent::OnDamageImpactReceived_Implementation(const FACFDamageEvent& damageEvent)
{
	PlayHitReactionEffect(damageEvent.HitResponseAction, damageEvent.DamageClass);

}

void UACFEffectsManagerComponent::PlayCurrentActionEffect( FEffect outEffect, ESpawnFXLocation locationSpawn, const FName& boneOrSocketName)
{
	outEffect.SpawnLocation = locationSpawn;
	outEffect.SocktOrBoneName = boneOrSocketName;

	UACFFunctionLibrary::PlayActionEffect(outEffect, CharacterOwner, this);
}

void UACFEffectsManagerComponent::PlayHitReactionEffect(const FGameplayTag& HitRection, const TSubclassOf<class UDamageType>& DamageType, ESpawnFXLocation locationSpawn /*= ESpawnFXLocation::ELastDamageLocation*/, const FName& boneOrSocketName/* = NAME_None*/) {

	FEffectByDamageType* effectList;
	if (HitRection == FGameplayTag()) {
		effectList = DamageEffectsByHitReaction.Find(UACFFunctionLibrary::GetDefaultHitState());
	}
	else {
		effectList = DamageEffectsByHitReaction.Find(HitRection);
	}

	if (effectList)
	{
		FEffect *effect = effectList->EffectByDamageType.Find(DamageType);
		if(effect){
			PlayCurrentActionEffect(*effect, locationSpawn, boneOrSocketName);
			return;
		}
	
		for (auto currentDam : effectList->EffectByDamageType) {
			if (DamageType->IsChildOf(currentDam.Key))
			{
				PlayCurrentActionEffect(currentDam.Value, locationSpawn, boneOrSocketName);
				return;
			}
		}
	}
}
