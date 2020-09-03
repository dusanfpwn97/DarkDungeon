// Copyright (C) Pakyman Prod. 2020. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "CCMData.h"
#include "CCMSequenceNotifyState.generated.h"

/**
 * 
 */
UCLASS()
class CINEMATICCAMERAMANAGER_API UCCMSequenceNotifyState : public UAnimNotifyState
{
	GENERATED_BODY()


public:

	virtual void NotifyBegin(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation, float TotalDuration) override;
	virtual void NotifyEnd(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation) override;
protected: 

	UPROPERTY(EditAnywhere, Category = CCM)
	bool bActivateOnlyIfOwningPlayer = true;

	UPROPERTY(EditAnywhere, Category = CCM)
	FCCMSequenceEvent SequenceModifier;
	
};
