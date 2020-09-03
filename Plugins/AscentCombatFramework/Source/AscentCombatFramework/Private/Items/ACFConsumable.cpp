// Copyright (C) Pakyman Prod. 2020. All Rights Reserved.

#include "Items/ACFConsumable.h"
#include "ARSStatisticsComponent.h"
#include "Actors/ACFCharacter.h"
#include "Game/ACFFunctionLibrary.h"




AACFConsumable::AACFConsumable()
{
	ItemInfo.ItemType = EItemType::Consumable;
	ItemInfo.Name = FText::FromString("Base Consumable");
	SetReplicates(true);
}


void AACFConsumable::Internal_UseItem( AACFCharacter* owner)
{
	if (owner)
	{
		ItemOwner = owner;

		UARSStatisticsComponent* statComp = ItemOwner->GetStatisticsComponent();
		if (statComp)
		{
			for (auto modifier : TimedAttributeSetModifier)
			{
				statComp->AddTimedAttributeSetModifier(modifier.modifier, modifier.duration);
			}
			for (auto statisMod : StatModifier)
			{
				statComp->ModifyStat(statisMod);
			}
		}

		UACFFunctionLibrary::PlayActionEffect(OnUsedEffect, ItemOwner, this);

		OnItemUsed();
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Invalid Item Owner - ACFConsumbale"));
	}

}

void AACFConsumable::OnItemUsed_Implementation()
{
	//IMPLEMENT ME!
}
