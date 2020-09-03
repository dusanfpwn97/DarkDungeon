// Copyright (C) Pakyman Prod. 2020. All Rights Reserved.

#include "AI/BehavioralThree/ACFCheckActionsBTService.h"
#include <BehaviorTree/BehaviorTreeComponent.h>
#include <BehaviorTree/BlackboardComponent.h>
#include "AI/ACFAIController.h"
#include "AI/Components/ACFCombatBehaviourComponent.h"

void UACFCheckActionsBTService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	UBlackboardComponent* const bbc = OwnerComp.GetBlackboardComponent();

	const AACFAIController* aiController = Cast<AACFAIController>(OwnerComp.GetAIOwner());

	if (aiController == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("UACFCheckActionsBTService get controller failed"));
		return;
	}

	UACFCombatBehaviourComponent* combatBehav = aiController->GetCombatBehavior();
	if (combatBehav == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("UACFCheckActionsBTService get behav failed"));
		return;
	}

	combatBehav->TryExecuteConditionAction();
}