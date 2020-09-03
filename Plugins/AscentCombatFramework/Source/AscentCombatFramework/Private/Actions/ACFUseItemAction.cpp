// Copyright (C) Pakyman Prod. 2020. All Rights Reserved.


#include "Actions/ACFUseItemAction.h"
#include "Components/ACFEquipmentComponent.h"
#include "Actors/ACFCharacter.h"


void UACFUseItemAction::OnActionStarted_Implementation()
{
	bSuccess = false;
}

void UACFUseItemAction::OnNotablePointReached_Implementation()
{
	UseItem();
	bSuccess = true;
}

void UACFUseItemAction::OnActionEnded_Implementation()
{
	if (!bSuccess && bShouldUseIfInterrupted)
		UseItem();
}

void UACFUseItemAction::UseItem()
{
	if (CharacterOwner)
	{
		UACFEquipmentComponent* equipComp = CharacterOwner->GetEquipmentComponent();
		if (equipComp)
			equipComp->UseItemBySlot(ItemSlot);
	}
}

bool UACFUseItemAction::CanExecuteAction_Implementation(class AACFCharacter* owner)
{
	if (!owner)
		return false;

	const UACFEquipmentComponent* equipComp = owner->GetEquipmentComponent();

	if (equipComp)
	{
		return equipComp->HasAnyItemInEquipmentSlot(ItemSlot);
	}
	return false;
}


