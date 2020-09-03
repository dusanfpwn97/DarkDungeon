// Copyright (C) Pakyman Prod. 2020. All Rights Reserved.


#include "Abilities/ACFAbility.h"
#include <GameFramework/Actor.h>

UWorld* UACFAbility::GetWorld() const
{
	if (actorOwner) {
		return actorOwner->GetWorld();
	}

	return nullptr;
}

bool UACFAbility::CanBeActivated_Implementation()
{
	return true;
}

void UACFAbility::OnAbilityActivated_Implementation()
{

}

void UACFAbility::OnAbilityDeactivated_Implementation()
{

}

void UACFAbility::Internal_OnActivated(class AActor* owner)
{
	actorOwner = owner;
	OnAbilityActivated();
}
