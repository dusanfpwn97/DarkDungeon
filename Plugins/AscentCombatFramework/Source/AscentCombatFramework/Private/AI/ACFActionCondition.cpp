// Copyright (C) Pakyman Prod. 2020. All Rights Reserved.


#include "AI/ACFActionCondition.h"
#include "Actors/ACFCharacter.h"
#include "AI/ACFAIController.h"
#include "ARSFunctionLibrary.h"
#include "ARSStatisticsComponent.h"


bool UACFDistanceActionCondition::IsConditionMet_Implementation(const  AACFAIController* controller)
  {
	if (!controller)
		return false;

	const AACFCharacter* owner = controller->GetBaseAICharacter();
	const AACFCharacter* target = Cast<AACFCharacter>(controller->GetTarget());

	if (!owner || !target)
		return false;

	switch (ConditionType)
	{
	case EConditionType::EAbove:
		return owner->GetDistanceTo(target) > Distance;
		break;
	case EConditionType::EBelow:
		return owner->GetDistanceTo(target) < Distance;
		break;
	case EConditionType::EEqual:
		return (owner->GetDistanceTo(target) > Distance - NearlyEqualAcceptance ||
			owner->GetDistanceTo(target) < Distance + NearlyEqualAcceptance);
		break;
	}

	return false;

}

bool UACFStatisticActionCondition::IsConditionMet_Implementation(const  AACFAIController* controller)
{
	if (!controller)
		return false;

	if (!UARSFunctionLibrary::IsValidStatisticTag(StatisticTag))
		return false;

	const AACFCharacter* owner = controller->GetBaseAICharacter();

	if (!owner)
		return false;

	const float statValue = owner->GetStatisticsComponent()->GetCurrentValueForStatitstic(StatisticTag);

	switch (ConditionType)
	{
	case EConditionType::EAbove:
		return statValue > StatisticValue;
		break;
	case EConditionType::EBelow:
		return statValue < StatisticValue;
		break;
	case EConditionType::EEqual:
		return (statValue > StatisticValue - NearlyEqualAcceptance ||
			statValue < StatisticValue + NearlyEqualAcceptance);
		break;
	}

	return false;
}
