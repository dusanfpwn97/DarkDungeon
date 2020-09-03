// Copyright (C) Pakyman Prod. 2020. All Rights Reserved.

#include "Actions/ACFShootAction.h"
#include "Items/ACFRangedWeapon.h"
#include "Actors/ACFCharacter.h"

UACFShootAction::UACFShootAction()
{

}

void UACFShootAction::OnActionStarted_Implementation()
{
	Super::OnActionStarted_Implementation();

	if (CharacterOwner)
	{
		UACFEquipmentComponent* equip = CharacterOwner->GetEquipmentComponent();
		AACFWeapon* weap = equip->GetCurrentMainWeapon();
		AACFRangedWeapon* rangedWeapon = Cast<AACFRangedWeapon>(weap);

		if (rangedWeapon)
		{
			rangedWeapon->Shoot();
		}
	}
}
