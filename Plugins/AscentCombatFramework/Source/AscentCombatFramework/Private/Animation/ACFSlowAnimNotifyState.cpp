// Copyright (C) Pakyman Prod. 2020. All Rights Reserved.


#include "Animation/ACFSlowAnimNotifyState.h"
#include "Runtime/Engine/Classes/Components/SkeletalMeshComponent.h"
#include "Runtime/Engine/Classes/Animation/AnimMontage.h"

void UACFSlowAnimNotifyState::NotifyBegin(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation, float TotalDuration)
{
	MeshComp->GlobalAnimRateScale = slowRate;
}

void UACFSlowAnimNotifyState::NotifyEnd(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation)
{
	MeshComp->GlobalAnimRateScale = previousRate;
}
