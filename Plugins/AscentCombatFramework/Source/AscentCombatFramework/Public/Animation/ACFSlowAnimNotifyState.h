// Copyright (C) Pakyman Prod. 2020. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "ACFSlowAnimNotifyState.generated.h"

class USkeletalMeshComponent;
/**
 * 
 */
UCLASS()
class ASCENTCOMBATFRAMEWORK_API UACFSlowAnimNotifyState : public UAnimNotifyState
{
	GENERATED_BODY()

	void NotifyBegin(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation, float TotalDuration) override;
	
	void NotifyEnd(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation) override;
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ACF)
		float previousRate = 1.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ACF)
		float slowRate = 0.2;
};
