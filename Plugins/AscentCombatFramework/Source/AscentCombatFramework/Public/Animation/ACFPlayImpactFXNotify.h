// Copyright (C) Pakyman Prod. 2020. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include <GameplayTagContainer.h>
#include "Game/ACFData.h"
#include "ACFPlayImpactFXNotify.generated.h"

/**
 * 
 */
UCLASS()
class ASCENTCOMBATFRAMEWORK_API UACFPlayImpactFXNotify : public UAnimNotify
{
	GENERATED_BODY()

protected:

	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;

	
public:

	UPROPERTY(EditAnywhere, Category = ACF)
	FGameplayTag HitReaction;

	UPROPERTY(EditAnywhere, Category = ACF)
	TSubclassOf<class UDamageType> DamageReceivedType;
	
	UPROPERTY(EditAnywhere, Category = ACF)
	ESpawnFXLocation SpawnLocation = ESpawnFXLocation::ESpawnAttachedToSocketOrBone;

	UPROPERTY(EditAnywhere, Category = ACF)
	FName SocketOrBoneLocation = NAME_None;

};
