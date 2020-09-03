// Copyright (C) Pakyman Prod. 2020. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "ACFNotifyExitAction.generated.h"

/**
 * 
 */
UCLASS()
class ASCENTCOMBATFRAMEWORK_API UACFNotifyExitAction : public UAnimNotify
{
	GENERATED_BODY()
	
protected:
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
	
	
};
