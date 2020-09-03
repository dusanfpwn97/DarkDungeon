// Copyright (C) Pakyman Prod. 2020. All Rights Reserved.

#include "Components/ACFEquipmentComponent.h"
#include "Items/ACFArmor.h"
#include "Game/ACFFunctionLibrary.h"
#include "Items/ACFWeapon.h"
#include <GameplayTagContainer.h>
#include "Items/ACFEquippableItem.h"
#include "ARSStatisticsComponent.h"
#include "Items/ACFWorldItem.h"
#include "Items/ACFConsumable.h"
#include "Items/ACFMeleeWeapon.h"
#include "Actors/ACFCharacter.h"
#include "Items/ACFRangedWeapon.h"
#include "Items/ACFItem.h"
#include "Net/UnrealNetwork.h"
#include <NavigationSystem.h>
#include <Kismet/KismetSystemLibrary.h>
#include <GameFramework/CharacterMovementComponent.h>
#include "Components/ACFDamageHandlerComponent.h"
#include "Items/ACFAccessory.h"


void UACFEquipmentComponent::GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(UACFEquipmentComponent, Equipment);
	DOREPLIFETIME(UACFEquipmentComponent, Inventory);
	DOREPLIFETIME(UACFEquipmentComponent, currentInventoryWeight);
	DOREPLIFETIME(UACFEquipmentComponent, CurrentlyEquippedSlotType);

}

void UACFEquipmentComponent::UseInventoryItem_Implementation(int32 index)
{
	if (Inventory.IsValidIndex(index))
	{
		FInventoryItem item = Inventory[index];

		if (!item.bIsEquipped)
		{
			EquipItemFromInventory(item);
		}		
		else
		{
			RemoveItemFromEquipment(item);
		}
	}
}

bool UACFEquipmentComponent::UseInventoryItem_Validate(int32 index)
{
	return true;
}

bool UACFEquipmentComponent::HasEnoughItemsOfType(const TArray<FBaseItem>&  ItemsToCheck) 
{
	for (auto item : ItemsToCheck) {

		int32 numberToCheck = item.Count;
		TArray<FInventoryItem*> invItems = FindItemsByClass(item.ItemClass);
		int32 TotItems = 0;
		for (auto invItem : invItems) {
			if (invItem) {
				TotItems += invItem->Count;
			}
		}

		if (TotItems < numberToCheck)
			return false;
	}
	return true;
}

void UACFEquipmentComponent::ConsumeItems_Implementation(const TArray<FBaseItem>& ItemsToCheck)
{
	for (auto item : ItemsToCheck) {
		TArray<FInventoryItem*> invItems = FindItemsByClass(item.ItemClass);
		if (invItems.IsValidIndex(0)) {
			RemoveItem(invItems[0]->Item, item.Count);
		}
	}
}

bool UACFEquipmentComponent::ConsumeItems_Validate(const TArray<FBaseItem>& ItemsToCheck)
{
	return true;
}

// Sets default values for this component's properties
UACFEquipmentComponent::UACFEquipmentComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
	SetIsReplicatedByDefault(true);
	Inventory.Empty();
}



void UACFEquipmentComponent::BeginPlay()
{
	Super::BeginPlay();

	if (GetOwner()->HasAuthority()) {
		UACFDamageHandlerComponent* damageHandler = GetOwner()->FindComponentByClass< UACFDamageHandlerComponent>();
		
		if (damageHandler) {
			damageHandler->OnOwnerDeath.AddDynamic(this, &UACFEquipmentComponent::OnEntityOwnerDeath);
		}
	}

}

void UACFEquipmentComponent::RefreshEquipmentAttachments()
{
	for (auto slot : Inventory)
	{
		if (slot.bIsEquipped && slot.Item)
		{
			EquipItemFromInventory(slot);
			slot.Item->SetActorRelativeLocation(FVector::ZeroVector);
			slot.Item->SetActorRelativeRotation(FRotator::ZeroRotator);
			AACFMeleeWeapon* weap = Cast<AACFMeleeWeapon>(slot.Item);
			if (weap && weap->LeftHandWeapon)
			{
				weap->LeftHandWeapon->SetActorRelativeLocation(FVector::ZeroVector);
				weap->LeftHandWeapon->SetActorRelativeRotation(FRotator::ZeroRotator);
			}
		}
	}

}

void UACFEquipmentComponent::DropItem_Implementation(const AACFItem* item, uint8 count /*= 1*/)
{
	if (!item || !item->GetItemInfo().bDroppable)
		return;

	SpawnWorldItem(count, item->GetClass());

	RemoveItem(item, count);
}

bool UACFEquipmentComponent::DropItem_Validate(const AACFItem* item, uint8 count /*= 1*/)
{
	return true;
}

bool UACFEquipmentComponent::RemoveItem_Validate(const AACFItem* item, uint8 count /*= 1*/)
{
	return true;
}

void UACFEquipmentComponent::RemoveItem_Implementation(const AACFItem* item, uint8 count /*= 1*/)
{
	if (!item)
		return;
	FInventoryItem* itemptr = Internal_GetInventoryItem(item);
	if (itemptr)
	{
		float HowMuchWeightRemoved = itemptr->Count*itemptr->ItemInfo.ItemWeight;
		itemptr->Count -= count;
		
		if (itemptr->bIsEquipped && Equipment.EquippedItems.Contains(item->GetItemSlot()))
		{
			int32 index = Equipment.EquippedItems.IndexOfByKey(item->GetItemSlot());
			 Equipment.EquippedItems[index].InventoryItem.Count = itemptr->Count;
			OnEquipmentChanged.Broadcast(Equipment);
		}
		if (itemptr->Count <= 0)
		{
			if (itemptr->bIsEquipped)
			{
				RemoveItemFromEquipment(*itemptr);
			}
			FInventoryItem tobeRemoved;
			if (GetInventoryItem(item, tobeRemoved))
				Inventory.Remove(tobeRemoved);
		}
		currentInventoryWeight-= HowMuchWeightRemoved;
		OnInventoryChanged.Broadcast(Inventory);
	}
}

void UACFEquipmentComponent::MoveItemToEquipment_Implementation(const AACFItem* item)
{
	if (item)
	{
		FInventoryItem outitem; 
		if (GetInventoryItem(item, outitem))
		{
			EquipItemFromInventory(outitem);
		}
	}
}

bool UACFEquipmentComponent::MoveItemToEquipment_Validate(const AACFItem* item)
{
	return true;
}

void UACFEquipmentComponent::AddItemToInventory_Implementation( AACFItem* itemToAdd, uint8 count /*= 1*/)
{
	Internal_AddItem(itemToAdd, count);
	return;
}


bool UACFEquipmentComponent::AddItemToInventory_Validate( AACFItem* itemToAdd, uint8 count /*= 1*/)
{
	return true;
}

void UACFEquipmentComponent::OnRep_Equipment()
{
	OnEquipmentChanged.Broadcast(Equipment);
}

void UACFEquipmentComponent::OnRep_Inventory()
{
	OnInventoryChanged.Broadcast(Inventory);
}

void UACFEquipmentComponent::OnEntityOwnerDeath()
{
	DestroyEquippedItems();
}

void UACFEquipmentComponent::AddWorldItemToInventory_Implementation(class AACFWorldItem* ItemToAdd, const TArray<int>& ItemToPick)
{
	if (ItemToAdd)
	{
		TArray<FBaseItem> gatheredItems;
		for (int i=0;i< ItemToPick.Num();i++)
		{
			int CurrentIndex= ItemToPick[i];
			FBaseItem* MatchedItem=nullptr;
			for (auto OneItem:ItemToAdd->GetItems())
			{
				if (OneItem.Index==CurrentIndex)
				{
					MatchedItem = &OneItem;
					break;
				}
			}
			if (MatchedItem)
			{
				uint8 addeditems = AddItemToInventoryByClass(MatchedItem->ItemClass, MatchedItem->Count, true);
				FBaseItem toAdd(MatchedItem->ItemClass, addeditems, CurrentIndex);
				gatheredItems.Add(toAdd);
			}
			
		}
		
		ItemToAdd->RemoveItemsByIndex(gatheredItems);
	}
}

bool UACFEquipmentComponent::AddWorldItemToInventory_Validate(class AACFWorldItem* ItemToAdd, const TArray<int>& ItemToPick)
{
	return true;
}

void UACFEquipmentComponent::UnequipArmor( FGameplayTag itemSlot)
{
	if (Equipment.EquippedItems.Contains(itemSlot) && ModularMeshes.Contains(itemSlot))
	{
		FInventoryItem invItem;
		if (GetEquippedItemSlot(itemSlot, invItem))
		{
			AACFArmor* internalArmor = Cast< AACFArmor>(invItem.Item);
			FModularPart outMesh;

			if (internalArmor && GetModularMesh(itemSlot, outMesh) && outMesh.meshComp)
			{
				internalArmor->Internal_OnUnEquipped();
				MarkItemOnInventoryAsEquipped(internalArmor, false);
				RemoveEquippedBySlot(internalArmor->GetItemSlot()); // Add this to clear old data

				outMesh.meshComp->SetSkeletalMesh(nullptr);
				OnEquipmentChanged.Broadcast(Equipment);
			}
		}

	}
}

bool UACFEquipmentComponent::CanBeEquipped(const AACFItem* equippable)
{
	if (equippable)
	{
		const AACFEquippableItem* _equip = Cast<AACFEquippableItem>(equippable);

		if (_equip && CharacterOwner && AvailableItemsSlot.Contains(_equip->GetItemSlot()))
		{
			UARSStatisticsComponent* _statcomp = CharacterOwner->GetStatisticsComponent();
			if (_statcomp)
			{
				return _statcomp->CheckAttributesRequirements(_equip->PrimaryAttributesRequirement);
			}
			else
			{
				UE_LOG(LogTemp, Log, TEXT("Add UARSStatisticsComponent to your character!! - ACFEquipmentComp"));
			}
		}
	}
	return false;
}

uint8 UACFEquipmentComponent::Internal_AddItem( AACFItem* itemToAdd, uint8 count)
{
	uint8 addeditemstotal = 0;
	uint8 addeditemstmp=0;
	bool bSuccessful = false;
	if (itemToAdd)
	{
		int itemweight= itemToAdd->GetItemInfo().ItemWeight;
		FString strtmp=itemToAdd->GetItemInfo().Name.ToString();
		float ftmp= (MaxInventoryWeight - currentInventoryWeight)/ itemweight;
		int32 maxAddableByWeightTotal = FMath::TruncToInt((MaxInventoryWeight - currentInventoryWeight) / itemToAdd->GetItemInfo().ItemWeight);
		if (maxAddableByWeightTotal<count)
		{
			count = maxAddableByWeightTotal;
		}
		int MaxInventoryStack = itemToAdd->GetItemInfo().MaxInventoryStack;
		TArray<FInventoryItem*> outItems = FindInInventoryByItemClass(itemToAdd);
		//IF WE ALREADY HAVE SOME ITEMS LIKE THAT, INCREMENT ACTUAL VALUE
		if (outItems.Num() > 0)
		{
			for (auto outItem : outItems) {
				if (outItem->Count < itemToAdd->GetItemInfo().MaxInventoryStack)
				{
					if (outItem->Count + count <= itemToAdd->GetItemInfo().MaxInventoryStack &&
						count * itemToAdd->GetItemInfo().ItemWeight + currentInventoryWeight <= MaxInventoryWeight)
					{
						addeditemstmp = count;
					}
					else
					{
						int32 maxAddableByStack = itemToAdd->GetItemInfo().MaxInventoryStack - outItem->Count;
						addeditemstmp = maxAddableByStack;
					}

					outItem->Count += addeditemstmp;
					addeditemstotal += addeditemstmp;
					count -= addeditemstmp;
					if (outItem->bIsEquipped && Equipment.EquippedItems.Contains(itemToAdd->GetItemSlot()))
					{
						int32 index = Equipment.EquippedItems.IndexOfByKey(itemToAdd->GetItemSlot());
						Equipment.EquippedItems[index].InventoryItem.Count = outItem->Count;
						OnEquipmentChanged.Broadcast(Equipment);

					}
					bSuccessful = true;
					//break;
				}
			}
		}
		//Otherwise we add new
		uint8 NumberOfItemNeed = FMath::CeilToInt((float)count / (float)itemToAdd->GetItemInfo().MaxInventoryStack);
		uint8 FreeSpaceInInventory = MaxInventorySlots - Inventory.Num();
		uint8 NumberOfStackToCreate = FGenericPlatformMath::Min(NumberOfItemNeed, FreeSpaceInInventory);
		for (int i = 0; i < NumberOfStackToCreate; i++)
		{
			if (Inventory.Num() < MaxInventorySlots)
			{
				FInventoryItem newItem(itemToAdd);
				if (count > itemToAdd->GetItemInfo().MaxInventoryStack)
					newItem.Count = itemToAdd->GetItemInfo().MaxInventoryStack;
				else
					newItem.Count = count;
				addeditemstotal += newItem.Count;
				count -= newItem.Count;
				Inventory.Add(newItem);
				bSuccessful = true;
			}
		}
		if (bSuccessful)
		{
			currentInventoryWeight += itemToAdd->GetItemInfo().ItemWeight * addeditemstotal;
			OnInventoryChanged.Broadcast(Inventory);
			return addeditemstotal;
		}
	}
	return addeditemstotal;
}

TArray<FInventoryItem*> UACFEquipmentComponent::FindInInventoryByItemClass(AACFItem * item)
{
	if(item == nullptr)
		return TArray<FInventoryItem*>();
	
	UClass* classToFind = item->GetClass();

	return FindItemsByClass(classToFind);

}

TArray<FInventoryItem*> UACFEquipmentComponent::FindItemsByClass(TSubclassOf<AACFItem> itemToFind)
{
	TArray<FInventoryItem*> foundItems;

	for (int i = 0; i < Inventory.Num(); i++) {
		if (Inventory[i].Item->GetClass() == itemToFind) {
			foundItems.Add(&Inventory[i]);
		}
	}
	return foundItems;
}

void UACFEquipmentComponent::AttachWeaponOnBody( AACFWeapon* WeaponToEquip)
{
	if (MainCharacterMesh)
	{
		FName _socket = WeaponToEquip->GetOnBodySocketName();
		WeaponToEquip->SetActorHiddenInGame(false);

		if (_socket != NAME_None)
		{
			WeaponToEquip->AttachToComponent(MainCharacterMesh, FAttachmentTransformRules::SnapToTargetIncludingScale, _socket);
		}
		else {
			UE_LOG(LogTemp, Log, TEXT("Remember to setup sockets in your weapon! - ACFEquipmentComp"));
		}
	}
}

void UACFEquipmentComponent::AttachWeaponOnHand(AACFWeapon* _localWeapon)
{
	FName _socket = _localWeapon->GetEquippedSocketName();
	if (_socket != NAME_None)
	{
		_localWeapon->AttachToComponent(MainCharacterMesh, FAttachmentTransformRules::SnapToTargetIncludingScale, _socket);
		_localWeapon->Internal_OnEquipped(CharacterOwner);
	}
	else {
		UE_LOG(LogTemp, Log, TEXT("Remember to setup sockets in your weapon! - ACFEquipmentComp"));
	}
}

uint8 UACFEquipmentComponent::AddItemToInventoryByClass(TSubclassOf<AACFItem> itemClass, uint8 count, bool bTryToEquip, float dropChanche)
{
	UWorld* world = GetWorld();
	AACFItem* _item = Cast<AACFItem>(world->SpawnActor(itemClass));

	if (!_item)
		return 0;


	_item->ForceNetUpdate();
	_item->SetActorHiddenInGame(true);

	int32 addedItems = Internal_AddItem(_item, count);

	FInventoryItem outItem;
	if (GetInventoryItem(_item, outItem))
	{
		ensure(addedItems <= count);
		outItem.DropChancePercentage = dropChanche;
		if (bAutoEquipItem && _item && !Equipment.EquippedItems.Contains(_item->GetItemSlot()) && bTryToEquip)
		{
			EquipItemFromInventory(outItem);
		}
	}
	return addedItems;
}

void UACFEquipmentComponent::EquipArmor_Implementation(AACFArmor* ArmorToEquip)
{
	if (!ArmorToEquip || !CanBeEquipped(ArmorToEquip))
		return;

	FInventoryItem outItem;
	if (GetInventoryItem(ArmorToEquip, outItem) && CharacterOwner)
	{
		if (Equipment.EquippedItems.Contains(ArmorToEquip->GetItemSlot()))
		{
			UnequipArmor(ArmorToEquip->GetItemSlot());
		}

		if (AddSkeletalMeshComponent(ArmorToEquip))
		{
			Equipment.EquippedItems.Add(FEquippedItem(ArmorToEquip->GetItemSlot(), outItem));
			ArmorToEquip->Internal_OnEquipped(CharacterOwner);
			MarkItemOnInventoryAsEquipped(ArmorToEquip, true);
			OnEquipmentChanged.Broadcast(Equipment);
		}
	}		
}

bool UACFEquipmentComponent::EquipArmor_Validate(AACFArmor* ArmorToEquip)
{
	return true;
}


void UACFEquipmentComponent::EquipWeapon_Implementation( AACFWeapon* WeaponToEquip)
  {

	if (!CanBeEquipped(WeaponToEquip))
		return;

	FInventoryItem outItem;
	
	if (GetInventoryItem(WeaponToEquip, outItem))
	{
		if (Equipment.EquippedItems.Contains(WeaponToEquip->GetItemSlot()))
		{
			UnequipOnBodyWeapon(WeaponToEquip->GetItemSlot());
		}
		WeaponToEquip->SetActorHiddenInGame(false);
		if (WeaponToEquip->LeftHandWeapon)
		{
			AttachWeaponOnBody(WeaponToEquip->LeftHandWeapon);
		}
		MarkItemOnInventoryAsEquipped(WeaponToEquip, true);
		Equipment.EquippedItems.Add(FEquippedItem(WeaponToEquip->GetItemSlot(), outItem));

		AttachWeaponOnBody(WeaponToEquip);
		OnEquipmentChanged.Broadcast(Equipment);
	}
}

bool UACFEquipmentComponent::EquipWeapon_Validate(AACFWeapon* WeaponToEquip)
{
	return true;
}


void UACFEquipmentComponent::EquipConsumable_Implementation(class AACFConsumable* itemToEquip)
{
	FInventoryItem outItem;

	if (GetInventoryItem(itemToEquip, outItem))
	{
		if (Equipment.EquippedItems.Contains(itemToEquip->GetItemSlot()))
		{
			UnequipOnBodyWeapon(itemToEquip->GetItemSlot());
		}

		MarkItemOnInventoryAsEquipped(itemToEquip, true);
		Equipment.EquippedItems.Add(FEquippedItem(itemToEquip->GetItemSlot(), outItem));
	
		OnEquipmentChanged.Broadcast(Equipment);
	}
}

bool UACFEquipmentComponent::EquipConsumable_Validate(class AACFConsumable* itemToEquip)
{
	return true;
}


void UACFEquipmentComponent::EquipAccessory_Implementation(class AACFAccessory* itemToEquip)
{
	if (!itemToEquip) {
		return;
	}

	FInventoryItem outItem;

	if (GetInventoryItem(itemToEquip, outItem))
	{
		if (Equipment.EquippedItems.Contains(itemToEquip->GetItemSlot()))
		{
			UnequipAccessory(itemToEquip->GetItemSlot());
		}
		itemToEquip->SetActorHiddenInGame(false);
		itemToEquip->Internal_OnEquipped(CharacterOwner);
		itemToEquip->AttachToComponent(MainCharacterMesh, FAttachmentTransformRules::SnapToTargetIncludingScale, itemToEquip->GetAttachmentSocket());
		MarkItemOnInventoryAsEquipped(itemToEquip, true);
		Equipment.EquippedItems.Add(FEquippedItem(itemToEquip->GetItemSlot(), outItem));

		OnEquipmentChanged.Broadcast(Equipment);
	}
}

bool UACFEquipmentComponent::EquipAccessory_Validate(class AACFAccessory* itemToEquip)
{
	return true;
}

void UACFEquipmentComponent::UnequipAccessory_Implementation(FGameplayTag itemSlot)
{
	if (Equipment.EquippedItems.Contains(itemSlot))
	{
		FInventoryItem invItem;
		if (GetEquippedItemSlot(itemSlot, invItem))
		{
			AACFAccessory* accessory = Cast< AACFAccessory>(invItem.Item);

			if (accessory)
			{
				accessory->Internal_OnUnEquipped();
				MarkItemOnInventoryAsEquipped(accessory, false);
				RemoveEquippedBySlot(accessory->GetItemSlot()); // Add this to clear old data
				accessory->SetActorHiddenInGame(true);
				OnEquipmentChanged.Broadcast(Equipment);
			}
		}

	}
}

bool UACFEquipmentComponent::UnequipAccessory_Validate(FGameplayTag itemSlot)
{
	return true;
}

void UACFEquipmentComponent::UseItemBySlot_Implementation(FGameplayTag ItemSlot)
{

	if (!UACFFunctionLibrary::IsValidItemSlotTag(ItemSlot))
	{
		UE_LOG(LogTemp, Log, TEXT("Invalid Weapon Slot Tag!!! - ACFEquipmentComp"));
		return;
	}

	if (ItemSlot == CurrentlyEquippedSlotType)
	{
		SheathCurrentWeapon();
		return;
	}

	FInventoryItem EquipSlot; 
	
	if(GetEquippedItemSlot(ItemSlot, EquipSlot))
	{		
		if (EquipSlot.Item->IsA(AACFWeapon::StaticClass()))
		{
			 AACFWeapon* _localWeapon = Cast<AACFWeapon>(EquipSlot.Item);
			if (Equipment.MainWeapon)
			{
				SheathCurrentWeapon();
			}

			Equipment.MainWeapon = _localWeapon;
			CurrentlyEquippedSlotType = ItemSlot;
		
			AttachWeaponOnHand(_localWeapon);

			if (_localWeapon->LeftHandWeapon)
			{
				Equipment.SecondaryWeapon = _localWeapon->LeftHandWeapon;
				AttachWeaponOnHand(_localWeapon->LeftHandWeapon);
			}
			
		}		
		else if (EquipSlot.Item->IsA(AACFConsumable::StaticClass()))
		{
			AACFConsumable* _consumable = Cast<AACFConsumable>(EquipSlot.Item);
			_consumable->Internal_UseItem(CharacterOwner);
			if (_consumable->bConsumeOnUse)
			{
				EquipSlot.Count -= 1;
				RemoveItem(_consumable);
			}		
		}
		OnEquipmentChanged.Broadcast(Equipment);
	}
}

bool UACFEquipmentComponent::UseItemBySlot_Validate(FGameplayTag WeaponSlot)
{
	return true;
}


void UACFEquipmentComponent::UnequipItemBySlot_Implementation(FGameplayTag itemSlot)
{
	if (!UACFFunctionLibrary::IsValidItemSlotTag(itemSlot))
	{
		UE_LOG(LogTemp, Log, TEXT("Invalid Weapon Slot Tag!!! - ACFEquipmentComp"));
		return;
	}

	if (itemSlot == CurrentlyEquippedSlotType)
	{
		SheathCurrentWeapon();
		return;
	}

	FInventoryItem EquipSlot;

	if (GetEquippedItemSlot(itemSlot, EquipSlot)) {
		RemoveItemFromEquipment(EquipSlot);
	}
}

bool UACFEquipmentComponent::UnequipItemBySlot_Validate(FGameplayTag itemSlot)
{
	return true;
}

void UACFEquipmentComponent::SheathCurrentWeapon_Implementation()
{	
	if (Equipment.MainWeapon)
	{
		FName _socket = Equipment.MainWeapon->GetOnBodySocketName();
		if (_socket != NAME_None)
		{
			Equipment.MainWeapon->AttachToComponent(MainCharacterMesh, FAttachmentTransformRules::SnapToTargetIncludingScale, _socket);
			Equipment.MainWeapon->Internal_OnUnEquipped();
			Equipment.MainWeapon = nullptr;		
		}
		else {
			UE_LOG(LogTemp, Log, TEXT("Remember to setup sockets in your weapon! - ACFEquipmentComp"));
		}

		if (Equipment.SecondaryWeapon)
		{
			_socket = Equipment.SecondaryWeapon->GetOnBodySocketName();
			if (_socket != NAME_None)
			{
				Equipment.SecondaryWeapon->AttachToComponent(MainCharacterMesh, FAttachmentTransformRules::SnapToTargetIncludingScale, _socket);
				Equipment.SecondaryWeapon->Internal_OnUnEquipped();
			}
			else {
				UE_LOG(LogTemp, Log, TEXT("Remember to setup sockets in your weapon! - ACFEquipmentComp"));
			}
		}
		Equipment.SecondaryWeapon = nullptr;
	}
	
	OnEquipmentChanged.Broadcast(Equipment);
	CurrentlyEquippedSlotType = UACFFunctionLibrary::GetMovesetTypeTagRoot();
}


bool UACFEquipmentComponent::SheathCurrentWeapon_Validate()
{
	return true;
}

void UACFEquipmentComponent::EquipItemFromInventory_Implementation(const FInventoryItem& item)
{
	if (item.Item && item.Item->IsA(AACFWeapon::StaticClass()))	{	
		EquipWeapon(Cast<AACFWeapon>(item.Item));
	}
	else if (item.Item && item.Item->IsA(AACFArmor::StaticClass()))	{
		EquipArmor(Cast<AACFArmor>(item.Item));
	}
	else if(item.Item && item.Item->IsA(AACFConsumable::StaticClass()))	{
		EquipConsumable(Cast<AACFConsumable>(item.Item));
	}
	else if (item.Item && item.Item->IsA(AACFAccessory::StaticClass())) {
		EquipAccessory(Cast<AACFAccessory>(item.Item));
	}
}

bool UACFEquipmentComponent::EquipItemFromInventory_Validate(const FInventoryItem& item)
{
	return true;
}

void UACFEquipmentComponent::DropItemFromInventory_Implementation(const FInventoryItem& item, int32 count)
{
	DropItem(item.Item, count);
}

bool UACFEquipmentComponent::DropItemFromInventory_Validate(const FInventoryItem& item, int32 count)
{
	return true;
}

void UACFEquipmentComponent::DropItemByInventoryIndex_Implementation(int32 itemIndex, int32 count)
{
	if (Inventory.IsValidIndex(itemIndex)) {
		DropItemFromInventory(Inventory[itemIndex], count);
	}
}

bool UACFEquipmentComponent::DropItemByInventoryIndex_Validate(int32 itemIndex, int32 count)
{
	return true;
}

void UACFEquipmentComponent::RemoveItemFromEquipment( FInventoryItem& item)
{
	if (item.Item == nullptr)
	{
		return;
	}
	if (item.Item->IsA(AACFWeapon::StaticClass()))
	{
		UnequipOnBodyWeapon(item.Item->GetItemSlot());
	}
	else if (item.Item->IsA(AACFArmor::StaticClass()))
	{
		UnequipArmor(item.Item->GetItemSlot());
	}
	else if (item.Item->IsA(AACFConsumable::StaticClass()))
	{
		UnequipConsumable(item.Item->GetItemSlot());
	}
	else if (item.Item->IsA(AACFAccessory::StaticClass())) {
		UnequipAccessory(item.Item->GetItemSlot());
	}
}



void UACFEquipmentComponent::UnequipConsumable(FGameplayTag Slot)
{
	if (!UACFFunctionLibrary::IsValidItemSlotTag(Slot))
	{
		UE_LOG(LogTemp, Log, TEXT("Invalid item Slot Tag!!! - ACFEquipmentComp"));
		return;
	}
	
	if (Equipment.EquippedItems.Contains(Slot))
	{
		int32 index = Equipment.EquippedItems.IndexOfByKey(Slot);
		MarkItemOnInventoryAsEquipped(Equipment.EquippedItems[index].InventoryItem.Item, false);
		Equipment.EquippedItems.RemoveAt(index);
		OnEquipmentChanged.Broadcast(Equipment);
	}

}

void UACFEquipmentComponent::MarkItemOnInventoryAsEquipped(const AACFItem* item, bool bIsEquipped)
{
	FInventoryItem* _item = Internal_GetInventoryItem(item);
	if (_item)
	{	
		_item->bIsEquipped = bIsEquipped;
	}
}

void UACFEquipmentComponent::RemoveEquippedBySlot(const FGameplayTag& slot)
{
	if (Equipment.EquippedItems.Contains(slot)) {
		int32 index = Equipment.EquippedItems.IndexOfByKey(slot);
		Equipment.EquippedItems.RemoveAt(index);
	}
}

void UACFEquipmentComponent::UnequipOnBodyWeapon_Implementation(FGameplayTag Slot)
{

	if (!UACFFunctionLibrary::IsValidItemSlotTag(Slot))
	{
		UE_LOG(LogTemp, Log, TEXT("Invalid Weapon Slot Tag!!! - ACFEquipmentComp"));
		return;
	}

	if (Slot.MatchesTagExact(CurrentlyEquippedSlotType)){
		SheathCurrentWeapon();
	}

	if (Equipment.EquippedItems.Contains(Slot)) {

		int32 index = Equipment.EquippedItems.IndexOfByKey(Slot);
		MarkItemOnInventoryAsEquipped(Equipment.EquippedItems[index].InventoryItem.Item, false);
		
		AACFWeapon* weap = Cast< AACFWeapon>(Equipment.EquippedItems[index].InventoryItem.Item);
		if (weap)
		{
			weap->SetActorHiddenInGame(true);
			if (weap->LeftHandWeapon)
			{
				weap->LeftHandWeapon->SetActorHiddenInGame(true);
				RemoveEquippedBySlot(weap->LeftHandWeapon->GetItemSlot());
			}
			
		}
		RemoveEquippedBySlot(Slot);
		OnEquipmentChanged.Broadcast(Equipment);

	}
}

bool UACFEquipmentComponent::UnequipOnBodyWeapon_Validate(FGameplayTag Slot)
{
	return true;
}


FInventoryItem* UACFEquipmentComponent::Internal_GetInventoryItem(const AACFItem * item)
{
	if (item == nullptr)
		return nullptr;
	return Inventory.FindByKey(item);
}

bool UACFEquipmentComponent::GetEquippedItemSlot( FGameplayTag itemSlot, FInventoryItem& outSlot) const
{

	if (Equipment.EquippedItems.Contains(itemSlot))
	{
		int32 index = Equipment.EquippedItems.IndexOfByKey(itemSlot);
		outSlot = Equipment.EquippedItems[index].InventoryItem;
		return true;
	}
	return false;
}

bool UACFEquipmentComponent::GetModularMesh( FGameplayTag itemSlot, FModularPart& outMesh) const
{
	const FModularPart* slot = ModularMeshes.FindByKey(itemSlot);
	if (slot)
	{
		outMesh = *slot;
		return true;
	}
	return false;
}

bool UACFEquipmentComponent::HasAnyItemInEquipmentSlot(FGameplayTag itemSlot) const
{
	return  Equipment.EquippedItems.Contains(itemSlot);
}

void UACFEquipmentComponent::SetDamageActivation(bool isActive, bool isSecondaryWeapon /*= false*/)
{
	AACFMeleeWeapon* weapon;
	if (isSecondaryWeapon && Equipment.SecondaryWeapon)	{
		weapon = Cast< AACFMeleeWeapon>(Equipment.SecondaryWeapon);
	}
	else	{
		weapon = Cast< AACFMeleeWeapon>(Equipment.MainWeapon);
	}

	if (weapon)
	{
		if (isActive) {
			weapon->StartWeaponSwing();
		}			
		else {
			weapon->StopWeaponSwing();
		}		
	}
}

bool UACFEquipmentComponent::CanSwitchToRanged()
{
	for (auto& weap : Equipment.EquippedItems)
	{
		if (weap.InventoryItem.Item->IsA(AACFRangedWeapon::StaticClass()))
		{
			return true;
		}
	}
	return false;

}

bool UACFEquipmentComponent::CanSwitchToMelee()
{
	for (auto& weap : Equipment.EquippedItems)
	{
		if (weap.InventoryItem.Item->IsA(AACFMeleeWeapon::StaticClass()))
		{
			return true;
		}
	}
	return false;
}

bool UACFEquipmentComponent::HasOnBodyAnyWeaponOfType(TSubclassOf<AACFWeapon> weaponClass) const
{
	for (auto weapon : Equipment.EquippedItems)
	{
		if (weapon.InventoryItem.Item->IsA(weaponClass))
		{
			return true;
		}
	}
	return false;
}

bool UACFEquipmentComponent::GetInventoryItem(const AACFItem* item, FInventoryItem& outItem)
{
	const FInventoryItem* _item = Internal_GetInventoryItem(item);
	if (_item)
	{
		outItem = *_item;
		return true; 
	}
	return false;
}

void UACFEquipmentComponent::InitializeInventoryAndEquipment()
{
	CharacterOwner = Cast<AACFCharacter>(GetOwner());
	if (CharacterOwner)
	{
		MainCharacterMesh = CharacterOwner->GetMesh();
	}
	if (GetOwner()->HasAuthority())
	{
		Inventory.Empty();
		currentInventoryWeight = 0.f;
		for (FStatingItem& item : StartingItems)
		{
			AddItemToInventoryByClass(item.ItemClass, item.Count, item.bAutoEquip, item.DropChancePercentage);

			if (Inventory.Num() > MaxInventorySlots)
			{
				UE_LOG(LogTemp, Log, TEXT("Invalid Inventory setup, too many slots on character!!! - ACFEquipmentComp"));
			}
		}
	}

}


void UACFEquipmentComponent::DestroyEquippedItems_Implementation()
{
	for (auto& weap : Equipment.EquippedItems)
	{
		if (weap.InventoryItem.Item)
		{
			weap.InventoryItem.Item->SetLifeSpan(1.f);
		}
	}
	if (bDropItemsOnDeath && Inventory.Num() > 0)
	{
		for (int32 Index = Inventory.Num() - 1; Index >= 0; --Index)
		{
			if (Inventory.IsValidIndex(Index) && Inventory[Index].DropChancePercentage > FMath::RandRange(0.f, 100.f))
			{
				DropItem(Inventory[Index].Item, Inventory[Index].Count);
			}
		}
	}	

}

bool UACFEquipmentComponent::DestroyEquippedItems_Validate()
{
	return true;
}

bool UACFEquipmentComponent::AddSkeletalMeshComponent(AACFArmor* ArmorToAdd)
{
	if (!ArmorToAdd->GetMeshComponent() || !ArmorToAdd->GetMeshComponent()->SkeletalMesh)
		return false;

	FModularPart outMesh;

	if (GetModularMesh(ArmorToAdd->GetItemSlot(), outMesh) && outMesh.meshComp)
	{
		
		outMesh.meshComp->SetSkeletalMesh(ArmorToAdd->GetMeshComponent()->SkeletalMesh);
		outMesh.meshComp->SetMasterPoseComponent(CharacterOwner->GetMesh());
	}
	else
	{
		USkeletalMeshComponent* NewComp = NewObject<USkeletalMeshComponent>(CharacterOwner, ArmorToAdd->GetItemSlot().GetTagName());
		if (!NewComp)
			return false;

		NewComp->RegisterComponent();        //You must ConstructObject with a valid Outer that has world, see above	 
		NewComp->SetWorldLocation(FVector::ZeroVector);
		NewComp->SetWorldRotation(FRotator::ZeroRotator);
		NewComp->AttachToComponent(CharacterOwner->GetMesh(), FAttachmentTransformRules(EAttachmentRule::SnapToTarget,true));
		NewComp->SetSkeletalMesh(ArmorToAdd->GetMeshComponent()->SkeletalMesh);
		NewComp->SetMasterPoseComponent(CharacterOwner->GetMesh());
		FModularPart mod ;
		mod.meshComp = NewComp;
		mod.ItemSlot = ArmorToAdd->GetItemSlot();
		ModularMeshes.Add(mod);
	}
	return true;
}

void UACFEquipmentComponent::SpawnWorldItem(uint8 count, TSubclassOf<AACFItem> item)
{	
	if (count >= 1 && CharacterOwner) {
		FVector startLoc = CharacterOwner->GetCharacterMovement()->GetActorFeetLocation();
		FBaseItem tobeAdded(item, count);
		TArray< FBaseItem> itemArray;
		itemArray.Add(tobeAdded);

		UACFFunctionLibrary::SpawnWorldItemNearLocation(this, itemArray, startLoc);
	}
}

int UACFEquipmentComponent::NumberOfItemCanTake(AACFItem* itemToCheck)
{
	
	uint8 addeditemstotal = 0;
	if (itemToCheck)
	{
		TArray<FInventoryItem*> outItems = FindInInventoryByItemClass(itemToCheck);
		int32 maxAddableByWeight = FMath::TruncToInt(MaxInventoryWeight - currentInventoryWeight / itemToCheck->GetItemInfo().ItemWeight);
		uint8 FreeSpaceInInventory = MaxInventorySlots - Inventory.Num();
		int32 maxAddableByStack = FreeSpaceInInventory* itemToCheck->GetItemInfo().MaxInventoryStack;
		//int32 maxAddableByStack = itemToCheck->GetItemInfo().MaxInventoryStack - outItem->Count;
		//IF WE ALREADY HAVE SOME ITEMS LIKE THAT, INCREMENT ACTUAL VALUE
		if (outItems.Num() > 0)
		{
			for (auto outItem : outItems) {
				maxAddableByStack+= itemToCheck->GetItemInfo().MaxInventoryStack - outItem->Count;
			}
		}
		addeditemstotal = FGenericPlatformMath::Min(maxAddableByStack, maxAddableByWeight);
		
	}
	return addeditemstotal;
}

void UACFEquipmentComponent::MoveItemToAnotherInventory_Implementation(UACFEquipmentComponent* OtherEquipmentComponent, class AACFItem* itemToMove, uint8 count /*= 1*/)
{
	if (!itemToMove)
	{
		return;
	}
	if (itemToMove->GetItemInfo().MaxInventoryStack > 1)
	{
		uint8 howmanycantake = OtherEquipmentComponent->NumberOfItemCanTake(itemToMove);
		if (howmanycantake < count)
		{
			count = howmanycantake;
		}
		int NumberToRemove = OtherEquipmentComponent->Internal_AddItem(itemToMove, count);
		//int NumberToRemove=OtherEquipmentComponent->AddItemToInventoryByClass(itemToMove->GetClass(), count, false);
		RemoveItem(itemToMove, NumberToRemove);
	}
	else
	{
		int NumberToRemove = OtherEquipmentComponent->Internal_AddItem(itemToMove,1);
		if (NumberToRemove==1)
		{
			RemoveItem(itemToMove);
		}
		
	}
	
}

bool UACFEquipmentComponent::MoveItemToAnotherInventory_Validate(UACFEquipmentComponent* OtherEquipmentComponent,class AACFItem* itemToMove, uint8 count /*= 1*/)
{
	return true;
}

