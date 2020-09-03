// Copyright (C) Pakyman Prod. 2020. All Rights Reserved.


#include "Abilities/ACFPassiveAbility.h"
#include "ARSStatisticsComponent.h"
#include <GameFramework/Actor.h>

void UACFPassiveAbility::OnAbilityActivated_Implementation()
{
	Super::OnAbilityActivated_Implementation();

	UARSStatisticsComponent* statComp = GetActorOwner()->FindComponentByClass<UARSStatisticsComponent>();
	if (statComp) {
		statComp->AddAttributeSetModifier(StatisticModifer);
	}

}

void UACFPassiveAbility::OnAbilityDeactivated_Implementation()
{
	Super::OnAbilityDeactivated_Implementation();

	UARSStatisticsComponent* statComp = GetActorOwner()->FindComponentByClass<UARSStatisticsComponent>();
	if (statComp) {
		statComp->RemoveAttributeSetModifier(StatisticModifer);
	}
}
