// Copyright (C) Pakyman Prod. 2020. All Rights Reserved.


#include "Abilities/ACFActionAbility.h"
#include "Components/ACFActionsManagerComponent.h"
#include <Components/ActorComponent.h>

void UACFActionAbility::OnAbilityActivated_Implementation()
{

	
	UACFActionsManagerComponent* actionsComp = GetActorOwner()->FindComponentByClass<UACFActionsManagerComponent>();
	if (actionsComp) {
		actionsComp->TriggerAction(ActionsToTrigger, AbilityPriority);
	}

	Super::OnAbilityActivated_Implementation();
}
