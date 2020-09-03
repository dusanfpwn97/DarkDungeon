// Copyright (C) Pakyman Prod. 2020. All Rights Reserved.

#include "AI/BehavioralThree/ACFUpdateCombatBTService.h"
#include <BehaviorTree/BehaviorTreeComponent.h>
#include "AI/ACFAIController.h"
#include <BehaviorTree/BlackboardComponent.h>
#include <GameFramework/Actor.h>
#include <BehaviorTree/Blackboard/BlackboardKeyType_Float.h>
#include <BehaviorTree/Blackboard/BlackboardKeyType_Object.h>
#include <Navigation/PathFollowingComponent.h>
#include "AI/Components/ACFCombatBehaviourComponent.h"
#include <AI/NavigationSystemBase.h>
#include <NavigationSystem.h>
#include "Game/ACFFunctionLibrary.h"

void UACFUpdateCombatBTService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	UBlackboardComponent* const bbc = OwnerComp.GetBlackboardComponent();

	 aiController = Cast<AACFAIController>(OwnerComp.GetAIOwner());

	if (aiController == nullptr )
	{
		UE_LOG(LogTemp, Warning, TEXT("UACFUpdateCombatBTService get controller failed"));
		return;
	}

	targetActor = aiController->GetTargetActorBK();
	if (targetActor == nullptr)
	{
		aiController->RequestAnotherTarget();
		return;
	}

	CharOwner = Cast<AACFCharacter> (aiController->GetPawn());

	if (CharOwner == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("GetPawn() is NULL - UACFUpdateCombatBTService"));
		return;
	}

	UpdateCombat();
}

void UACFUpdateCombatBTService::UpdateCombat()
{
	float distanceToTarget;
	ACharacter* targetChar = Cast< ACharacter>(targetActor);
	if (targetChar) {
		distanceToTarget = UACFFunctionLibrary::CalculateDistanceBetweenCharactersExtents(CharOwner, targetChar);
	}
	else {
		distanceToTarget = CharOwner->GetDistanceTo(targetActor);
	}
	
	aiController->SetTargetActorDistanceBK(distanceToTarget);

	if (distanceToTarget > aiController->GetLoseTargetDistance()) {
		aiController->SetTarget(nullptr);
	}

   combatBehav = aiController->GetCombatBehavior();

	if (combatBehav)
	{
		EAICombatState combatState = combatBehav->GetBestCombatStateByTargetDistance(distanceToTarget);// aiController->GetCombatStateBK();

		switch (combatState) 
		{
		case EAICombatState::EMeleeCombat:
			if (aiController->GetComboCounterBK() > MaxComboCount && combatBehav->EvaluateCombatState(EAICombatState::EMeleePostAttack))
			{
				SetNewMaxComboCount();
				combatState = EAICombatState::EMeleePostAttack;
			}
			combatBehav->DefaultCombatBehaviorType = ECombatBehaviorType::EMelee;
			break;
		}
		if (combatState != aiController->GetCombatStateBK())
			aiController->SetCombatStateBK(combatState);
	}	
}

void UACFUpdateCombatBTService::SetNewMaxComboCount()
{
	MaxComboCount = FMath::TruncToInt(FMath::RandRange(combatBehav->MinMeleeComboAttacks, combatBehav->MaxMeleeComboAttacks));
}
