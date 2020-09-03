// Copyright (C) Pakyman Prod. 2020. All Rights Reserved.

#include "AI/Components/ACFGroupAIComponent.h"
#include "Game/ACFPlayerController.h"
#include <Engine/World.h>
#include <GameFramework/Pawn.h>
#include "AI/ACFAIController.h"
#include <Kismet/KismetSystemLibrary.h>
#include "Actors/ACFCharacter.h"
#include <Kismet/GameplayStatics.h>
#include "Game/ACFFunctionLibrary.h"
#include "AI/Components/ACFThreatManagerComponent.h"


// Sets default values for this component's properties
UACFGroupAIComponent::UACFGroupAIComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	bInBattle = false;
	SetIsReplicatedByDefault(true);
	spawnOffset.X = 200.f;

}

void UACFGroupAIComponent::GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);


}
// Called when the game starts
void UACFGroupAIComponent::BeginPlay()
{
	Super::BeginPlay();
	SetReferences();
}

void UACFGroupAIComponent::SetReferences()
{
	groupLead = Cast<AActor>(GetOwner());
}

void UACFGroupAIComponent::SendCommandToCompanions_Implementation(FGameplayTag command)
{
	Internal_SendCommandToAgents(command);
}

bool UACFGroupAIComponent::SendCommandToCompanions_Validate(FGameplayTag command)
{
	return true;
}

void UACFGroupAIComponent::SpawnGroup_Implementation()
{
	if (bAlreadySpawned && !CanSpawnMultitpleTimes)
	{
	//	ensure(false);
		return;
	}
	Internal_SpawnGroup();
	bAlreadySpawned = true;
	InitAgents();

}

 bool UACFGroupAIComponent::SpawnGroup_Validate() {
	 return true;
}

void UACFGroupAIComponent::InitAgents()
{
	for (int32 index = 0; index < AICharactersInfo.Num(); index++)
	{
		if(AICharactersInfo.IsValidIndex(index))
			InitAgent(AICharactersInfo[index], index);
	}
}

void UACFGroupAIComponent::InitAgent(FAIAgentsInfo& agent, int32 childIndex)
{
	if (agent.AICharacter && !agent.AIController)
	{
		agent.AICharacter->SpawnDefaultController();
		agent.AIController = Cast<AACFAIController>(agent.AICharacter->GetController());
	}		

	if (agent.AIController && agent.AICharacter)
	{
		agent.AIController->SetGroupOwner(this, childIndex, bOverrideAgentPerception);
		agent.AIController->SetLeadActorBK(groupLead);
		agent.AIController->SetDefaultState(DefaultAiState);
		agent.AIController->SetCurrentAIStateBK(DefaultAiState);
		if (bOverrideAgentTeam) {
			agent.AICharacter->AssignTeam(CombatTeam);
		}
	}
}

void UACFGroupAIComponent::Internal_SendCommandToAgents(FGameplayTag command)
{
	for (FAIAgentsInfo achar : AICharactersInfo)
	{
		if (achar.AIController)
		{
			achar.AIController->TriggerCommand(command);
		}
	}
}

void UACFGroupAIComponent::SetEnemyGroup(UACFGroupAIComponent* inEnemyGroup)
{
	if (inEnemyGroup && UACFFunctionLibrary::AreEnemyTeams(GetCombatTeam(), inEnemyGroup->GetCombatTeam()))
		enemyGroup = inEnemyGroup;
}

class AACFCharacter* UACFGroupAIComponent::RequestNewTarget(const AACFAIController* requestSender)
{
	//First Try to help lead
	AACFCharacter* lead = Cast< AACFCharacter>(requestSender->GetLeadActorBK());
	if (lead)
	{
		AACFCharacter* newTarget = Cast< AACFCharacter>(lead->GetTarget());
		if (newTarget && newTarget->IsMyEnemy(requestSender->GetBaseAICharacter()))
			return Cast< AACFCharacter>(lead->GetTarget());
	}

	//Then Try to help other in  the group
	if (AICharactersInfo.IsValidIndex(0) && AICharactersInfo[0].AICharacter->IsValidLowLevel() && AICharactersInfo[0].AIController->IsValidLowLevel())
	{
		for (FAIAgentsInfo achar : AICharactersInfo)
		{
			if (achar.AIController && achar.AIController != requestSender)
			{
				AACFCharacter* newTarget = Cast< AACFCharacter>(achar.AIController->GetTargetActorBK());
				if (newTarget && newTarget->IsAlive() && achar.AIController->GetAIStateBK() == EAIState::EBattle)
				{
					return newTarget;
				}
			}
		}
	}

	//Then Try to help other in  the group
	if (enemyGroup)
	{
		return enemyGroup->GetAgentNearestTo(requestSender->GetPawn()->GetActorLocation());
	}

	return nullptr;
}

void UACFGroupAIComponent::Internal_SpawnGroup()
{

	if (AIToSpawn.Num() > 0)
	{
		UWorld* const world = GetWorld();

		if (world)
		{
			FActorSpawnParameters spawnParam;
			spawnParam.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

			// offset on forward direction
			 xOffset = spawnOffset.X;
			 yOffset = spawnOffset.Y;

			 maxGroupWidth = -1;
			 maxGroupLength = -1;

			 childGroupIndex = 0;

			// the first row of current class
			 fi_currClassRowBase = 0;
			 colPadding = 0;
			 rowPadding = 0;

			for (int iClass = 0; iClass < AIToSpawn.Num(); iClass++)
			{
				TSubclassOf<AACFCharacter> ClassToSpawn = AIToSpawn[iClass].AIClassBP;
				int Remain = AIToSpawn[iClass].TotalNumber;
				int maxRowSize = AIToSpawn[iClass].MaxNumOfCol;
				ensure(maxRowSize > 0);
				colPadding = AIToSpawn[iClass].ColumnPadding;
				rowPadding = AIToSpawn[iClass].RowPadding;

				if (Remain == 0)
				{
					UE_LOG(LogTemp, Error, TEXT("MaxNumOfCol can not be zero - UACFGroupAIComponent::Internal_SpawnGroup"));
					return;
				}
				// find out how many row we have for this class
				while (Remain > 0)
				{
					int temp = Remain - maxRowSize;
					if (temp > 0)
					{
						FormationInfo.Add(maxRowSize);
						Remain = temp;
					}
					else
					{
						FormationInfo.Add(Remain);
						break;
					}
				}

				int maxRow = FormationInfo.Num() - fi_currClassRowBase;
				for (int iRow = 0; iRow < maxRow; iRow++)
				{
					int currentRow = fi_currClassRowBase + iRow;
					int currentRowSize = FormationInfo[currentRow];
					float rowWidth = (currentRowSize - 1) * colPadding;
					if (rowWidth > maxGroupWidth)
						maxGroupWidth = rowWidth;
					float centerOffset = 0.5f * rowWidth;

					for (int iCol = 0; iCol < currentRowSize; iCol++)
					{
						yOffset = iCol * colPadding - centerOffset;
						// Spawn
						childGroupIndex = AddAgentToGroup(xOffset, yOffset,  ClassToSpawn);
						if (childGroupIndex == -1)
							return;
					}
					xOffset += rowPadding;
				}
				fi_currClassRowBase += maxRow;
				AIToSpawn[iClass].NumOfRow = maxRow;
			}
		}
		bAlreadySpawned = true;
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("%s NO AI to Spawn - AAIFGROUPPAWN::SpawnAGroup"), *this->GetName());
	}
}


uint8 UACFGroupAIComponent::AddAgentToGroup(float inXOffset, float inYOffset, TSubclassOf<AACFCharacter> ClassToSpawn)
{
	UWorld* const world = GetWorld();

	ensure(GetOwner()->HasAuthority());

	if (!world)
		return -1;

	if (!groupLead) {
		SetReferences();
		if(!groupLead){
			return -1;
		}
	}
		

	if (AICharactersInfo.Num() >= MaxSimultaneousAgents) {
		return -1;
	}
		

	FAIAgentsInfo newCharacterInfo;

	FVector myLocation = GetComponentLocation();
	FVector spawnLocation =
		myLocation - inXOffset * groupLead->GetActorForwardVector() +
		inYOffset * groupLead->GetActorRightVector();
	FTransform spawnTransform;
	spawnTransform.SetLocation(spawnLocation);
	spawnTransform.SetRotation(groupLead->GetActorQuat());
	/*spawnTransform.SetScale3D(FVector(1.0f, 1.0f, 1.0f));*/

	newCharacterInfo.AICharacter
		= world->SpawnActorDeferred<AACFCharacter>(
			ClassToSpawn, spawnTransform, nullptr, nullptr,
			ESpawnActorCollisionHandlingMethod::AlwaysSpawn);

	if (newCharacterInfo.AICharacter)
	{
		UGameplayStatics::FinishSpawningActor(newCharacterInfo.AICharacter, spawnTransform);

		// End Spawn
		newCharacterInfo.AICharacter->SpawnDefaultController();
		uint8 localGroupIndex = AICharactersInfo.Num();
		newCharacterInfo.AIController = Cast<AACFAIController>(newCharacterInfo.AICharacter->GetController());
		if (newCharacterInfo.AIController)
		{			
			InitAgent(newCharacterInfo, localGroupIndex);
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("%s NO AI to Spawn - AAIFGROUPPAWN::SpawnAGroup"), *this->GetName());
		}

		AICharactersInfo.Add(newCharacterInfo);
		return localGroupIndex;
	}	
	return 0;
}

uint8 UACFGroupAIComponent::AddExistingCharacterToGroup(AACFCharacter* character)
{
	UWorld* const world = GetWorld();

	if (!world)
		return 0;

	if (!groupLead)
		return 0;

	if (AICharactersInfo.Contains(character))
		return 0;

	FAIAgentsInfo newCharacterInfo;
	newCharacterInfo.AICharacter = character;

	if (newCharacterInfo.AICharacter)
	{
		if(!newCharacterInfo.AICharacter->GetController())
			newCharacterInfo.AICharacter->SpawnDefaultController();

		uint8 childIndex = AICharactersInfo.Num();
		newCharacterInfo.AIController = Cast<AACFAIController>(newCharacterInfo.AICharacter->GetController());
		if (newCharacterInfo.AIController)
		{
			InitAgent(newCharacterInfo, childIndex);
			if (bInBattle && newCharacterInfo.AIController->GetAIStateBK() != EAIState::EBattle && AICharactersInfo.Num() != 0)
			{
				newCharacterInfo.AIController->SetTarget(AICharactersInfo[0].AICharacter->GetTarget());
			}
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("%s NO AI to Spawn - AAIFGROUPPAWN::SpawnAGroup"), *this->GetName());
		}

		AICharactersInfo.Add(newCharacterInfo);
		return childIndex;
	}
	return 0;
}



AACFCharacter* UACFGroupAIComponent::GetAgentNearestTo(const FVector& location)
{
	AACFCharacter* bestAgent = nullptr;
	float minDistance = 999999.f;
	for (FAIAgentsInfo achar : AICharactersInfo)
	{
		if (achar.AICharacter && achar.AICharacter->IsAlive())
		{
			float distance = FVector::Distance(location, achar.AICharacter->GetActorLocation());
			if (distance <= minDistance)
			{
				minDistance = distance;
				bestAgent = achar.AICharacter;
			}
		}
	}
	return bestAgent;
}


bool UACFGroupAIComponent::RemoveAgentFromGroup(AACFCharacter* character)
{
	if (!character)
		return false;

	AACFAIController* contr = Cast<AACFAIController>(character->GetController());
	if (!contr)
		return false;

 	const FAIAgentsInfo agentInfo(character, contr);

	if (AICharactersInfo.Contains(agentInfo))
	{
		AICharactersInfo.RemoveSingle(agentInfo);
		return true;
	}
 		
	return false;
}

void UACFGroupAIComponent::SetInBattle(bool inBattle, AActor* newTarget)
{
	bInBattle = inBattle;
	if (bInBattle)
	{
		for (FAIAgentsInfo achar : AICharactersInfo)
		{
			if (achar.AIController)
			{
				UACFThreatManagerComponent* threatComp = achar.AIController->GetThreatManager();
				if (newTarget && threatComp && achar.AICharacter->IsAlive() && achar.AIController->GetAIStateBK() != EAIState::EBattle)
				{
					threatComp->AddThreat(newTarget, threatComp->GetDefaultThreatForActor(newTarget));
				}
			}
		}
	}
}

void UACFGroupAIComponent::OnChildDeath(int _childIndex)
{
	OnAgentDeath.Broadcast(_childIndex);
	Internal_RemoveAgentAtIndex(_childIndex);
}

void UACFGroupAIComponent::Internal_RemoveAgentAtIndex(int _childIndex)
{
	if (AICharactersInfo.IsValidIndex(_childIndex))
	{
		AICharactersInfo.RemoveAt(_childIndex);
	}

	for (int32 i = 0; i < AICharactersInfo.Num(); i++)
	{
		if (AICharactersInfo.IsValidIndex(i))
		{
			AICharactersInfo[i].AIController->SetGroupOwner(this, i, bOverrideAgentPerception);
		}
	}
}


