// Copyright (C) Pakyman Prod. 2020. All Rights Reserved.

#include "AI/ACFGroupAIController.h"
#include "AI/ACFAIGroupSpawner.h"
#include "AI/Components/ACFGroupAIComponent.h"
#include "Game/ACFData.h"
#include "AI/ACFAIController.h"
#include <UObject/Class.h>
#include <GameFramework/Actor.h>
#include "Interfaces/ACFEntityInterface.h"
#include "Game/ACFFunctionLibrary.h"
#include <Perception/AIPerceptionComponent.h>


void AACFGroupAIController::BeginPlay()
{
	Super::BeginPlay();

	
	if (PerceptionComponent) {
		PerceptionComponent->OnTargetPerceptionUpdated.AddDynamic(this, &AACFGroupAIController::HandlePerceptionUpdated);
	}
}

void AACFGroupAIController::EndPlay(EEndPlayReason::Type reason)
{
	Super::EndPlay(reason);

	if (PerceptionComponent) {
		PerceptionComponent->OnTargetPerceptionUpdated.RemoveDynamic(this, &AACFGroupAIController::HandlePerceptionUpdated);
	}
}

void AACFGroupAIController::HandlePerceptionUpdated(AActor* Actor, FAIStimulus Stimulus)
{
	if (!bUseGroupPerception)
		return;

	IACFEntityInterface* entity = Cast<IACFEntityInterface>(Actor);
	if (!entity) {
		return;
	}

	AACFAIGroupSpawner* groupAI = Cast<AACFAIGroupSpawner>(GetPawn());
	if (!groupAI)
		return;


	UACFGroupAIComponent* groupComp = groupAI->GetAIGroupComponent();
	if (!groupComp)
		return;

	if(!UACFFunctionLibrary::AreEnemyTeams(groupAI->GetCombatTeam(),
		IACFEntityInterface::Execute_GetEntityCombatTeam(Actor))) {
		return;
	}



	AACFAIGroupSpawner* advGroup = Cast< AACFAIGroupSpawner>(Actor);
	if (advGroup) {

		TArray<FAIAgentsInfo> agents;
		groupComp->GetGroupAgents(agents);
		for (FAIAgentsInfo agent : agents)
		{
			if (agent.AIController && agent.AICharacter) {
				int32 index = agent.AIController->GetIndexInGroup();
				FAIAgentsInfo outAgent;
				if (advGroup->GetAgentWithIndex(index, outAgent)) {
					agent.AIController->HandlePerceptionUpdated(outAgent.AICharacter, Stimulus);

				}
				else {
					AACFCharacter* adv = advGroup->GetAgentNearestTo(agent.AICharacter->GetActorLocation());
					agent.AIController->HandlePerceptionUpdated(adv, Stimulus);
				}
			}
		}
	}
	else {
		TArray<FAIAgentsInfo> agents;
		groupComp->GetGroupAgents(agents);

		for (FAIAgentsInfo agent : agents)
		{
			if (agent.AIController) {
				agent.AIController->HandlePerceptionUpdated(Actor, Stimulus);

			}
			//Added because on savegame controller could not be spawned at first frame
			else if (agent.AICharacter)
				agent.AIController = Cast<AACFAIController>(agent.AICharacter->GetController());
		}

	}

	
}
