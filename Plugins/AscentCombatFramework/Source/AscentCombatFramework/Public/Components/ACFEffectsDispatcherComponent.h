// Copyright (C) Pakyman Prod. 2020. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Game/ACFData.h"
#include "ACFEffectsDispatcherComponent.generated.h"


UCLASS( ClassGroup=(ACF), meta=(BlueprintSpawnableComponent) )
class ASCENTCOMBATFRAMEWORK_API UACFEffectsDispatcherComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UACFEffectsDispatcherComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:

	UFUNCTION(NetMulticast, Reliable, WithValidation, Category = ACF)
	void ClientsPlayEffect(const FEffect& effect, class AACFCharacter* instigator );


	void SpawnSoundAndParticleAttached(const FEffect& effect, class AACFCharacter* instigator);
	void SpawnSoundAndParticleAtLocation(const FEffect& effect, const FVector& location);

public:	

	UFUNCTION(BlueprintCallable, Server, WithValidation, Reliable,  Category = ACF)
	void ServerPlayReplicatedEffect(const FEffect& effect, class AACFCharacter* instigator);

	UFUNCTION(BlueprintCallable, Category = ACF)
	void PlayEffectLocally(const FEffect& effect, class AACFCharacter* instigator);

	void Internal_PlayEffect(class AACFCharacter* instigator, const FEffect& effect);

};
