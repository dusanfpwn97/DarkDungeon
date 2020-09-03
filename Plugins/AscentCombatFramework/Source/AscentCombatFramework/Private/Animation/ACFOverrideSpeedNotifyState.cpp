// Copyright (C) Pakyman Prod. 2020. All Rights Reserved.


#include "Animation/ACFOverrideSpeedNotifyState.h"
#include <Components/SkeletalMeshComponent.h>
#include <Animation/AnimSequenceBase.h>
#include "Components/ACFLocomotionComponent.h"

UACFOverrideSpeedNotifyState::UACFOverrideSpeedNotifyState()
{

}

void UACFOverrideSpeedNotifyState::NotifyBegin(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation, float TotalDuration)
{
	
	UACFLocomotionComponent* LocComp = MeshComp->GetOwner()->FindComponentByClass<UACFLocomotionComponent>();
	if (LocComp) {
		LocComp->SetMontageReprodutionType(EMontageReproductionType::ECurveOverrideSpeed);
	}
}

void UACFOverrideSpeedNotifyState::NotifyEnd(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation)
{
	UACFLocomotionComponent* LocComp = MeshComp->GetOwner()->FindComponentByClass<UACFLocomotionComponent>();
	if (LocComp) {
		LocComp->SetMontageReprodutionType(EMontageReproductionType::ERootMotion);
	}
}
