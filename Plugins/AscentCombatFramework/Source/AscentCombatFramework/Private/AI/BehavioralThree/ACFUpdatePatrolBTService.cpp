// Copyright (C) Pakyman Prod. 2020. All Rights Reserved.

#include "AI/BehavioralThree/ACFUpdatePatrolBTService.h"
#include <BehaviorTree/BlackboardComponent.h>
#include <BehaviorTree/BehaviorTreeComponent.h>
#include "AI/ACFAIController.h"
#include "Actors/ACFCharacter.h"
#include <GameFramework/Pawn.h>


void UACFUpdatePatrolBTService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	UBlackboardComponent* const bbc = OwnerComp.GetBlackboardComponent();

	aiController = Cast<AACFAIController>(OwnerComp.GetAIOwner());

	if (aiController == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("UACFUpdateCombatBTService get controller failed"));
		return;
	}

	CharOwner = aiController->GetPawn();

	if (CharOwner == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("GetPawn() is NULL - UACFUpdateCombatBTService"));
		return;
	}


	float distanceToTarget = (CharOwner->GetActorLocation() - aiController->GetTargetPointLocationBK()).Size();
	aiController->SetTargetPointDistanceBK(distanceToTarget);

}

