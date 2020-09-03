// Copyright (C) Pakyman Prod. 2020. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include <Perception/AIPerceptionTypes.h>
#include "ACFGroupAIController.generated.h"

/**
 * 
 */
UCLASS()
class ASCENTCOMBATFRAMEWORK_API AACFGroupAIController : public AAIController
{
	GENERATED_BODY()

protected:

	UPROPERTY(EditAnywhere, Category = ACF)
	bool bUseGroupPerception = true;


	virtual void BeginPlay() override;

	virtual void EndPlay(EEndPlayReason::Type reason) override;

private: 

	UFUNCTION()
	void HandlePerceptionUpdated(AActor* Actor, FAIStimulus Stimulus);
	
};
