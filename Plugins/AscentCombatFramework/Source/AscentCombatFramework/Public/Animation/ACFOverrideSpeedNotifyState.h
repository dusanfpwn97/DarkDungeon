// Copyright (C) Pakyman Prod. 2020. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "ACFOverrideSpeedNotifyState.generated.h"

/**
 * 
 */
class USkeletalMeshComponent;
class UAnimSequenceBase;

UCLASS()
class ASCENTCOMBATFRAMEWORK_API UACFOverrideSpeedNotifyState : public UAnimNotifyState
{
	GENERATED_BODY()

	UACFOverrideSpeedNotifyState();

protected:


	virtual void NotifyBegin(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation, float TotalDuration) override;
	virtual void NotifyEnd(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation) override;
	
};
