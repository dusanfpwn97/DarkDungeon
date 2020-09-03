// Copyright (C) Pakyman Prod. 2020. All Rights Reserved.

#include "AI/BehavioralThree/ACFUpdateStateBTService.h"
#include "AI/ACFAIController.h"
#include <BehaviorTree/BehaviorTreeComponent.h>
#include "AI/Components/ACFCommandsManagerComponent.h"

void UACFUpdateStateBTService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
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
		aiController->Destroy();
		return;
	}
	AActor* lead = aiController->GetLeadActorBK();
	if (lead)
	{
		float distanceFromLeader = (CharOwner->GetActorLocation() - lead->GetActorLocation()).Size();
		aiController->SetHomeDistanceBK(distanceFromLeader);

		if (aiController->ShouldTeleportHome() && distanceFromLeader >= aiController->GetTeleportHomeDistanceTrigger()) {
			aiController->TeleportNearLead();
			return;
		}
		if (aiController->ShouldCameHome() && aiController->GetAIStateBK() != EAIState::EFollowLeader)
		{
			if (distanceFromLeader > aiController->GetMaxDistanceFromLead() )
			{
				aiController->SetCurrentAIStateBK(EAIState::EFollowLeader);
			}
		}
	}
	

}

