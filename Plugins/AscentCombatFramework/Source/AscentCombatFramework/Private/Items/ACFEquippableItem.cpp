// Copyright (C) Pakyman Prod. 2020. All Rights Reserved.

#include "Items/ACFEquippableItem.h"
#include "ARSStatisticsComponent.h"
#include <GameFramework/Character.h>
#include "Actors/ACFCharacter.h"
#include <Kismet/GameplayStatics.h>
#include <Sound/SoundCue.h>

AACFEquippableItem::AACFEquippableItem()
{
	bReplicates = true;
	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));

	Mesh->SetRelativeLocation(FVector(0.f, 0.f, 0.f));
}

void AACFEquippableItem::Internal_OnEquipped(AACFCharacter* _owner)
{
	if (_owner)
	{
		ItemOwner = _owner;
		SetOwner(ItemOwner);
		if (EquipSound && ItemOwner->IsAlive()) {
			UGameplayStatics::PlaySoundAtLocation(this, EquipSound, GetActorLocation());
		}
		AddModifierToOwner(AttributeModifier);
		OnItemEquipped();
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Invalid owner -AACFEquippableItem "));
	}
}


void AACFEquippableItem::RemoveModifierToOwner(FAttributesSetModifier _attributeModifier)
{
	if (ItemOwner)
	{
		UARSStatisticsComponent* _statcomp = ItemOwner->FindComponentByClass<UARSStatisticsComponent>();
		if (_statcomp)
		{
			_statcomp->RemoveAttributeSetModifier(_attributeModifier);
		}

	}
}

void AACFEquippableItem::AddModifierToOwner(FAttributesSetModifier _attributeModifier)
{
	if (ItemOwner)
	{
		UARSStatisticsComponent* _statcomp = ItemOwner->FindComponentByClass<UARSStatisticsComponent>();
		if (_statcomp)
		{
			_statcomp->AddAttributeSetModifier(_attributeModifier);
		}

	}
}

void AACFEquippableItem::Internal_OnUnEquipped()
{
	RemoveModifierToOwner( AttributeModifier);

	if (UnequipSound && ItemOwner->IsAlive()) {
		UGameplayStatics::PlaySoundAtLocation(this, UnequipSound, GetActorLocation());
	}
	OnItemUnEquipped();
}


void AACFEquippableItem::OnItemEquipped_Implementation()
{

}

void AACFEquippableItem::OnItemUnEquipped_Implementation()
{

}

