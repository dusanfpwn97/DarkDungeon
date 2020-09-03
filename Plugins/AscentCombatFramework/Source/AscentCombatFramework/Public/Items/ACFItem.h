// Copyright (C) Pakyman Prod. 2020. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include <Engine/DataTable.h>
#include <GameplayTagContainer.h>
#include "ACFItemTypes.h"
#include "ACFItem.generated.h"

USTRUCT(BlueprintType)
struct FBaseItem : public FTableRowBase
{
	GENERATED_BODY()

public:

	FBaseItem() {};

	FBaseItem(TSubclassOf<class AACFItem> inItem, uint8 inCount,uint8 inIndex=0) {
		ItemClass = inItem;
		Count = inCount;
		Index= inIndex;
	};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ACF)
	TSubclassOf<class AACFItem> ItemClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ACF)
	uint8 Count = 1;

	UPROPERTY(BlueprintReadWrite, Category = ACF)
	uint8 Index = 0;

	FORCEINLINE	bool operator==(const FBaseItem& Other) const
	{
		return this->ItemClass == Other.ItemClass;
	}

	FORCEINLINE	bool operator!=(const FBaseItem& Other) const
	{
		return this->ItemClass != Other.ItemClass;
	}

	FORCEINLINE	bool operator!=(const TSubclassOf<class AACFItem>& Other) const
	{
		return this->ItemClass != Other;
	}

	FORCEINLINE	bool operator==(const TSubclassOf<class AACFItem>& Other) const
	{
		return this->ItemClass == Other;
	}
};

USTRUCT(BlueprintType)
struct FItemDescriptor : public FTableRowBase
{
	GENERATED_BODY()

public:
	
	/*Icon to be displayed in UI*/
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = ACF)
	class UTexture2D* ThumbNail;

	/*Name of the item*/
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = ACF)
	FText Name;

	/*Long description of the item*/
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = ACF)
	FText Description;

	/*Type of item*/
	UPROPERTY(BlueprintReadOnly, Category = ACF)
	EItemType ItemType;

	/*Decide the amount of stackable units when this item is in inventory*/
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = ACF)
	uint8 MaxInventoryStack = 1;

	/*Weight of this item in the inventory*/
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = ACF)
	float ItemWeight = 5.0;

	/*mesh to be used when spawned in world as world mesh, not mandatory*/
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = ACF)
	UStaticMesh* WorldMesh;

	/* If the item is droppable in the world*/
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = ACF)
	bool bDroppable = true;

	/*Unique Identifier for the item in the level*/
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = ACF)
	int32 GUID;

	/* If this item can be crafted*/
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = ACF)
	bool bCraftable = true;

	/* The items required to craft this*/
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (EditCondition = "bCraftable == true"), Category = ACF)
	TArray<FBaseItem> RequiredItems;

	/* If this item can be upgraded*/
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = ACF)
	bool bUpgradable = false;

	/* The items required to upgrade this item*/
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (EditCondition = "bUpgradable == true"), Category = ACF)
	TArray<FBaseItem> RequiredItemsToUpgrade;

	/* Next level of this item*/
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (EditCondition = "bUpgradable == true"), Category = ACF)
	TSubclassOf<AACFItem> NextLevelClass;

	/*If upgrading this item has a cost in currency*/
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = ACF)
	float UpgradeCurrencyCost = 0.f;

	/*base price for selling / buying this item*/
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = ACF)
	float CurrencyValue = 5.0;

	/*Slot in which this item is equipped*/
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "ACF | Item")
	FGameplayTag ItemSlot;

};

UCLASS()
class ASCENTCOMBATFRAMEWORK_API AACFItem : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AACFItem();

	UFUNCTION(BlueprintPure, Category = ACF)
	FORCEINLINE class UTexture2D* GetThumbnailImage() const { return ItemInfo.ThumbNail; }

	UFUNCTION(BlueprintPure, Category = ACF)
	FORCEINLINE  FText GetItemName() const { return ItemInfo.Name; }

	UFUNCTION(BlueprintPure, Category = ACF)
	FORCEINLINE  FText GetItemDescription() const { return ItemInfo.Description; }

	UFUNCTION(BlueprintPure, Category = ACF)
	FORCEINLINE  EItemType GetItemType() { return ItemInfo.ItemType; }

	UFUNCTION(BlueprintPure, Category = ACF)
	FORCEINLINE  class AACFCharacter* GetItemOwner() { return ItemOwner; }

	UFUNCTION(BlueprintPure, Category = ACF)
	FORCEINLINE  int32 GetGUID() const { return ItemInfo.GUID; }

	UFUNCTION(BlueprintPure, Category = ACF)
   	FORCEINLINE  FItemDescriptor GetItemInfo() const { return ItemInfo; }

	UFUNCTION(BlueprintPure, Category = ACF)
	FORCEINLINE  FGameplayTag GetItemSlot() const { return ItemInfo.ItemSlot; }
private:


protected:

	UPROPERTY(BlueprintReadOnly, Category = ACF)
	class AACFCharacter* ItemOwner;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "ACF | Item")
	FItemDescriptor ItemInfo;


	
};
