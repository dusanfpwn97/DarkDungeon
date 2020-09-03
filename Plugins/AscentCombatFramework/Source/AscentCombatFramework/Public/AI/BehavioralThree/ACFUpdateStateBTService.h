// Copyright (C) Pakyman Prod. 2020. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "ACFUpdateStateBTService.generated.h"

/**
 * 
 */
UCLASS()
class ASCENTCOMBATFRAMEWORK_API UACFUpdateStateBTService : public UBTService
{
	GENERATED_BODY()

protected:


	UPROPERTY(BlueprintReadOnly, Category = ACF)
	class AACFAIController*  aiController;

	UPROPERTY(BlueprintReadOnly, Category = ACF)
	class  APawn*  CharOwner;

public:
	
	void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
