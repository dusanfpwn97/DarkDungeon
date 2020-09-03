// Copyright (C) Pakyman Prod. 2020. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "ACFNotifyAction.generated.h"

/**
 * 
 */
UCLASS()
class ASCENTCOMBATFRAMEWORK_API UACFNotifyAction : public UAnimNotify
{
	GENERATED_BODY()
	
protected: 
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
	
public:

	UPROPERTY(EditAnywhere, Category = ACF)
	bool bActivateOnlyOnServer = true;
};
