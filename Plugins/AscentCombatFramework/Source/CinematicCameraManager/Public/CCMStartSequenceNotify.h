// Copyright (C) Pakyman Prod. 2020. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "CCMStartSequenceNotify.generated.h"

/**
 * 
 */
UCLASS()
class CINEMATICCAMERAMANAGER_API UCCMStartSequenceNotify : public UAnimNotify
{
	GENERATED_BODY()

protected:
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;

public:

	UPROPERTY(EditAnywhere, Category = ACF)
	FName SequenceName = NAME_None;
	
};
