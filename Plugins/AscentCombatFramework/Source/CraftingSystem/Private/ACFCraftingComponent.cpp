// Copyright (C) Pakyman Prod. 2020. All Rights Reserved.


#include "ACFCraftingComponent.h"
#include "Game/ACFPlayerController.h"
#include "Game/ACFFunctionLibrary.h"
#include "ACFCurrencyComponent.h"
#include "Components/ACFEquipmentComponent.h"

// Sets default values for this component's properties
UACFCraftingComponent::UACFCraftingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
}


bool UACFCraftingComponent::CanPlayerBuyItems(const FBaseItem& itemToBuy) const
{
	if (!SellableItems.Contains(itemToBuy.ItemClass)) {
		return false;
	}

	const FBaseItem* tobeSold = SellableItems.FindByKey(itemToBuy.ItemClass);
	if (tobeSold && tobeSold->Count >= itemToBuy.Count) {
		FItemDescriptor itemToBuyDesc;
		if (TryGetItemDescriptor(itemToBuy, itemToBuyDesc)) {
			return (itemToBuyDesc.CurrencyValue * itemToBuy.Count * PriceMultiplierOnSell) <= GetPlayerCurrency();
		}
	}

	return false;
}

bool UACFCraftingComponent::TryBuyItems(const FBaseItem& item)
{
	if (!CanPlayerBuyItems(item)) {
		return false;
	}

	FItemDescriptor itemToBuyDesc;
	if (TryGetItemDescriptor(item, itemToBuyDesc)) {
		float totalCost = (itemToBuyDesc.CurrencyValue * item.Count * PriceMultiplierOnSell);
		UACFCurrencyComponent* currencyComp = GetPlayerCurrencyComponent();
		UACFEquipmentComponent* equipComp = GetPlayerEquipment();
		if (currencyComp && equipComp) {
			currencyComp->RemoveCurrency(totalCost);
			UWorld* world = GetWorld();
			AACFItem* _item = Cast<AACFItem>(world->SpawnActor(item.ItemClass));
			equipComp->AddItemToInventory(_item, item.Count);
			RemoveSoldItems(item);
			if (sellerCurrency) {
				sellerCurrency->AddCurrency(totalCost);
			}
			OnSellableItemsChanged.Broadcast(SellableItems);
			return true;
		}
	}
	return false;
}

bool UACFCraftingComponent::TryCraftItem(TSubclassOf<AACFItem> ItemClass)
{
	if (!CanPlayerCraftItem(ItemClass)) {
		return false;
	}
	UACFEquipmentComponent* equipComp = GetPlayerEquipment();

	FItemDescriptor itemToCraftDesc;

	if (!equipComp || !TryGetItemDescriptorByClass(ItemClass, itemToCraftDesc)) {
		return false;
	}

	equipComp->ConsumeItems(itemToCraftDesc.RequiredItems);
	UWorld* world = GetWorld();
	AACFItem* _item = Cast<AACFItem>(world->SpawnActor(ItemClass));
	equipComp->AddItemToInventory(_item, 1);
	return true;
}

bool UACFCraftingComponent::CanPlayerCraftItem(TSubclassOf<AACFItem> itemToCraft) const
{
	if (!CraftableItems.Contains(itemToCraft)) {
		return false;
	}

	UACFEquipmentComponent* equipComp = GetPlayerEquipment();

	FItemDescriptor itemToCraftDesc;

	if (!equipComp || !TryGetItemDescriptorByClass(itemToCraft, itemToCraftDesc)) {
		return false;
	}

	if (!itemToCraftDesc.bCraftable) {
		return false;
	}

	return equipComp->HasEnoughItemsOfType(itemToCraftDesc.RequiredItems);

}

bool UACFCraftingComponent::TryGetItemDescriptor(const FBaseItem& item, FItemDescriptor& outItemDescriptor) const
{
	if (item.ItemClass) {		
		return TryGetItemDescriptorByClass(item.ItemClass, outItemDescriptor);
	}
	return false;
}

bool UACFCraftingComponent::TryGetItemDescriptorByClass(TSubclassOf<AACFItem> ItemClass, FItemDescriptor& outItemDescriptor) const
{
	if (ItemClass) {
		UWorld* world = GetWorld();
		AACFItem* _item = Cast<AACFItem>(world->SpawnActor(ItemClass));
		AACFItem* itemObject = Cast<AACFItem>(_item);
		if (itemObject) {
			outItemDescriptor = itemObject->GetItemInfo();
			return true;
		}
	}
	return false;
}

float UACFCraftingComponent::GetPlayerCurrency() const
{
	const AACFPlayerController* playerContr = UACFFunctionLibrary::GetLocalACFPlayerController(this);
	if (playerContr) {
		UACFCurrencyComponent* currency = playerContr->FindComponentByClass<UACFCurrencyComponent>();
		if (currency) {
			return currency->GetCurrentCurrencyAmount();
		}
	}
	return 0.f;
}





class UACFEquipmentComponent* UACFCraftingComponent::GetPlayerEquipment() const
{
	const AACFCharacter* playerChar = UACFFunctionLibrary::GetLocalACFPlayerCharacter(this);
	if (playerChar) {
		return playerChar->GetEquipmentComponent();
	}
	UE_LOG(LogTemp, Warning, TEXT("Invalid ACFPlayerCharacter! - UACFVendorComponent::GetPlayerEquipment  "));
	return nullptr;
}

class TArray<FInventoryItem> UACFCraftingComponent::GetPlayerInventory() const
{
	const UACFEquipmentComponent* equipComp = GetPlayerEquipment();

	if (equipComp) {
		return equipComp->GetInventory();
	}
	return TArray<FInventoryItem>();
}

class UACFCurrencyComponent* UACFCraftingComponent::GetPlayerCurrencyComponent() const
{
	const AACFPlayerController* playerContr = UACFFunctionLibrary::GetLocalACFPlayerController(this);
	if (playerContr) {
		return playerContr->FindComponentByClass<UACFCurrencyComponent>();;
	}
	UE_LOG(LogTemp, Warning, TEXT("Invalid ACFPlayerCharacter! - UACFVendorComponent::GetPlayerEquipment  "));

	return nullptr;
}

TArray<FInventoryItem> UACFCraftingComponent::GetAllPlayerUpgradableItems() const
{
	TArray<FInventoryItem> upgradables;

	TArray<FInventoryItem> playerInventory = GetPlayerInventory();

	for (auto elem : playerInventory) {
		if (elem.Item && elem.Item->GetItemInfo().bUpgradable) {
			upgradables.Add(elem);
		}
	}
	return upgradables;
}

bool UACFCraftingComponent::CanPlayerUpgradeItem(const FInventoryItem& itemToUpgrade) const
{
	if (!GetPlayerInventory().Contains(itemToUpgrade)) {
		return false;
	}

	UACFEquipmentComponent* equipComp = GetPlayerEquipment();

	if (equipComp && itemToUpgrade.Item) {

		FItemDescriptor itemInfo = itemToUpgrade.Item->GetItemInfo();
		if (itemInfo.bUpgradable && GetPlayerCurrency() >= PriceMultiplierOnSell * itemInfo.UpgradeCurrencyCost) {
			return equipComp->HasEnoughItemsOfType(itemInfo.RequiredItemsToUpgrade);
		}
		
	}
	return false;
}

bool UACFCraftingComponent::TryUpgradeItem(const FInventoryItem& itemToUpgrade)
{
	if (!CanPlayerUpgradeItem(itemToUpgrade)) {
		return false;
	}

	UACFEquipmentComponent* equipComp = GetPlayerEquipment();
	UACFCurrencyComponent* currencyComp = GetPlayerCurrencyComponent();
	if (equipComp && currencyComp && itemToUpgrade.Item ) {
		FItemDescriptor itemInfo = itemToUpgrade.Item->GetItemInfo();

		if (itemInfo.NextLevelClass) {
			equipComp->ConsumeItems(itemInfo.RequiredItemsToUpgrade);
			currencyComp->RemoveCurrency(PriceMultiplierOnSell * itemInfo.UpgradeCurrencyCost);
			equipComp->RemoveItem(itemToUpgrade.Item, 1);
			UWorld* world = GetWorld();
			AACFItem* _item = Cast<AACFItem>(world->SpawnActor(itemInfo.NextLevelClass));
			AACFItem* itemToAdd = Cast< AACFItem>(_item);
			if (itemToAdd) {
				equipComp->AddItemToInventory(itemToAdd, 1);
				return true;
			}
		}	
	}
	return false;
}

bool UACFCraftingComponent::CanPlayerSellItemFromHisInventory(const class AACFItem* itemTobeSold, int32 count /*= 1*/)
{
	UACFEquipmentComponent* equipComp = GetPlayerEquipment(); 
	if (!sellerCurrency || !equipComp) {
		return false;
	}

	FInventoryItem invItem;
	if (equipComp->GetInventoryItem(itemTobeSold, invItem)) {
		return invItem.Count >= count &&
			itemTobeSold->GetItemInfo().CurrencyValue * count * PriceMultiplierOnBuy <= sellerCurrency->GetCurrentCurrencyAmount();
	}

	return false;
}

bool UACFCraftingComponent::TrySellItemFromPlayerInventory(const class AACFItem* itemTobeSold, int32 count /*= 1*/)
{
	if (!CanPlayerSellItemFromHisInventory(itemTobeSold, count)) {
		return false;
	}

	UACFEquipmentComponent* equipComp = GetPlayerEquipment();
	UACFCurrencyComponent* currencyComp = GetPlayerCurrencyComponent();
	float totalCost = itemTobeSold->GetItemInfo().CurrencyValue * count * PriceMultiplierOnBuy;
	if (equipComp && currencyComp) {
		equipComp->RemoveItem(itemTobeSold, count);
		currencyComp->AddCurrency(totalCost);
		sellerCurrency->RemoveCurrency(totalCost);
		if (SellableItems.Contains(itemTobeSold->GetClass()))
		{
			auto ExistItem = SellableItems.FindByKey(itemTobeSold->GetClass());
			ExistItem->Count+= count;
		}
		else
		{
			SellableItems.Add(FBaseItem(itemTobeSold->GetClass(), count));
		}
		
		OnSellableItemsChanged.Broadcast(SellableItems);
		return true;
	}
	return false;
}

float UACFCraftingComponent::GetVendorCurrency()
{
	return sellerCurrency->GetCurrentCurrencyAmount();
}

// Called when the game starts
void UACFCraftingComponent::BeginPlay()
{
	Super::BeginPlay();

	sellerCurrency = GetOwner()->FindComponentByClass<UACFCurrencyComponent>();
	if (!sellerCurrency) {
		UE_LOG(LogTemp, Warning, TEXT("Seller with No Currencies! - UACFVendorComponent::BeginPlay"));
	}
}

void UACFCraftingComponent::RemoveSoldItems(const FBaseItem& item)
{
	int32 index;
	if (SellableItems.Find(item, index)) {
		SellableItems[index].Count -= item.Count;

		if (SellableItems[index].Count <= 0) {
			SellableItems.RemoveAt(index);
		}
	}
}


