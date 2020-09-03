// Copyright (C) Pakyman Prod. 2020. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Items/ACFItem.h"
#include "Components/ACFEquipmentComponent.h"
#include "ACFCraftingComponent.generated.h"
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnVendorItemChanged, const TArray<FBaseItem>&, Items);


UCLASS(Blueprintable, ClassGroup = (ACF), meta = (BlueprintSpawnableComponent))
class CRAFTINGSYSTEM_API UACFCraftingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UACFCraftingComponent();

	UFUNCTION(BlueprintCallable, Category = ACF)
	bool CanPlayerBuyItems(const FBaseItem& itemsToBuy) const;

	UFUNCTION(BlueprintCallable, Category = ACF)
	bool CanPlayerCraftItem(TSubclassOf<AACFItem> itemToCraft) const;

	UFUNCTION(BlueprintCallable, Category = ACF)
	bool TryGetItemDescriptor(const FBaseItem& item, FItemDescriptor& outItemDescriptor) const;

	UFUNCTION(BlueprintCallable, Category = ACF)
	bool TryGetItemDescriptorByClass(TSubclassOf<AACFItem> ItemClass, FItemDescriptor& outItemDescriptor) const;

	UFUNCTION(BlueprintPure, Category = ACF)
	float GetPlayerCurrency() const;

	UFUNCTION(BlueprintCallable, Category = ACF)
	bool TryBuyItems(const FBaseItem& item);

	UFUNCTION(BlueprintCallable, Category = ACF)
	bool TryCraftItem(TSubclassOf<AACFItem> ItemClass);

	UFUNCTION(BlueprintPure, Category = ACF)
	class UACFEquipmentComponent* GetPlayerEquipment() const;

	UFUNCTION(BlueprintPure, Category = ACF)
	TArray<FInventoryItem> GetPlayerInventory() const;

	UFUNCTION(BlueprintPure, Category = ACF)
	class UACFCurrencyComponent* GetPlayerCurrencyComponent() const;

	UFUNCTION(BlueprintPure, Category = ACF)
	TArray<FInventoryItem> GetAllPlayerUpgradableItems() const;

	UFUNCTION(BlueprintCallable, Category = ACF)
	bool CanPlayerUpgradeItem(const FInventoryItem& itemToUpgrade) const;

	UFUNCTION(BlueprintCallable, Category = ACF)
	bool TryUpgradeItem(const FInventoryItem& itemToUpgrade);

	UFUNCTION(BlueprintCallable, Category = ACF)
	bool CanPlayerSellItemFromHisInventory(const class AACFItem* itemTobeSold, int32 count = 1);

	UFUNCTION(BlueprintCallable, Category = ACF)
	bool TrySellItemFromPlayerInventory(const class AACFItem* itemTobeSold, int32 count = 1);

	UFUNCTION(BlueprintCallable, Category = ACF)
	float GetVendorCurrency();

	/*Used to prompt the client that sellableitems have changed*/
	UPROPERTY(BlueprintAssignable, Category = ACF)
	FOnVendorItemChanged OnSellableItemsChanged;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	/*Items this vendor can sell*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = ACF)
	TArray<FBaseItem> SellableItems;

	/*Items this vendor can craft*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = ACF)
	TArray<TSubclassOf<AACFItem>> CraftableItems;

	/*The multiplier this vendor is going to apply to the item value when selling to the player*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = ACF)
	float PriceMultiplierOnSell = 1.f;

	/*The multiplier this vendor is going to apply to the item value when buying from the player*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = ACF)
	float PriceMultiplierOnBuy = 0.2f;

private:

	void RemoveSoldItems(const FBaseItem& item);

	UPROPERTY()
	UACFCurrencyComponent* sellerCurrency;


};
