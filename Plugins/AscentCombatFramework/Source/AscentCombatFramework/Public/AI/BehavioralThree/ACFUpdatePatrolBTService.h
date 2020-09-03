// Copyright (C) Pakyman Prod. 2020. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "ACFUpdatePatrolBTService.generated.h"

/**
 * 
 */
UCLASS()
class ASCENTCOMBATFRAMEWORK_API UACFUpdatePatrolBTService : public UBTService
{
	GENERATED_BODY()
protected: 

	UPROPERTY(BlueprintReadOnly, Category = ACF)
	class AACFAIController*  aiController;

	UPROPERTY(BlueprintReadOnly, Category = ACF)
	class  APawn*  CharOwner;
	

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
