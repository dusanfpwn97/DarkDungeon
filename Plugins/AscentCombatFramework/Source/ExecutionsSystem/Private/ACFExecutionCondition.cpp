// Copyright (C) Pakyman Prod. 2020. All Rights Reserved.


#include "ACFExecutionCondition.h"
#include "ARSStatisticsComponent.h"
#include "CASAnimCondition.h"
#include "CASAnimSlaveComponent.h"
#include "Game/ACFFunctionLibrary.h"
#include <GameFramework/Character.h>

bool UACFExecutionCondition::VerifyCondition_Implementation(const FName& animTag, const ACharacter* animMaster) 
{
	if (FMath::RandRange(0.f, 100.f) > ExecutionChance) {
		return false;
	}
	if (!animMaster) {
		return false;
	}

	UARSStatisticsComponent* statComp = animMaster->FindComponentByClass< UARSStatisticsComponent>();
	UARSStatisticsComponent* ownerStatComp = GetOwnerComponent()->GetCharacterOwner()->FindComponentByClass< UARSStatisticsComponent>();
	if (statComp && ownerStatComp) {
		float damage = statComp->GetParameterValue(ExecutorParameterToCheck);
		FGameplayTag healthTag = UACFFunctionLibrary::GetHealthTag();
		float health = ownerStatComp->GetCurrentValueForStatitstic(healthTag);
		if (damage * ParameterScalarMultiplier > health) {
			return true;
		}
	}

	return false;

}
