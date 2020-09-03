// Copyright (C) Pakyman Prod. 2020. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include <Components/SkeletalMeshComponent.h>
#include <Engine/DataTable.h>
#include <GameplayTagContainer.h>
#include "Items/ACFItemTypes.h"
#include "Items/ACFItem.h"
#include "ACFEquipmentComponent.generated.h"



USTRUCT(BlueprintType)
struct FStatingItem : public FBaseItem
{
	GENERATED_BODY()

public:

	FStatingItem() {};

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = ACF)
		bool bAutoEquip = true;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (ClampMin = "0.0", ClampMax = "100.0"), Category = ACF)
		float DropChancePercentage = 100.f;

	FORCEINLINE	bool operator==(const FStatingItem& Other) const
	{
		return this->ItemClass == Other.ItemClass;
	}

	FORCEINLINE	bool operator!=(const FStatingItem& Other) const
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
struct FInventoryItem : public FTableRowBase
{
	GENERATED_BODY()

public:

	FInventoryItem() {};

	FInventoryItem(AACFItem* inItem) {
		if (inItem)
		{
			Item = inItem;
			ItemInfo = Item->GetItemInfo();
		}
	};

	UPROPERTY(SaveGame, BlueprintReadOnly, Category = ACF)
	class AACFItem* Item;

	UPROPERTY(SaveGame, BlueprintReadOnly, Category = ACF)
	 FItemDescriptor ItemInfo;

	UPROPERTY(SaveGame, BlueprintReadOnly, Category = ACF)
		int32 Count = 1;

	UPROPERTY(SaveGame,  BlueprintReadOnly, Category = ACF)
		bool bIsEquipped = false;

	UPROPERTY(SaveGame, BlueprintReadOnly, meta = (ClampMin = "0.0", ClampMax = "100.0"), Category = ACF)
		float DropChancePercentage = 100.f;

	FORCEINLINE	bool operator==(const FInventoryItem& Other) const
	{
		return ItemInfo.GUID == Other.ItemInfo.GUID;
	}

	FORCEINLINE	bool operator!=(const FInventoryItem& Other) const
	{
		return ItemInfo.GUID != Other.ItemInfo.GUID;
	}

	FORCEINLINE	bool operator!=(const class AACFItem* Other) const
	{
		return  this->Item->GetGUID() != Other->GetGUID();
	}

	FORCEINLINE	bool operator==(const class AACFItem* Other) const
	{
		return this->Item->GetGUID() == Other->GetGUID();
	}

};

USTRUCT(BlueprintType)
struct FEquippedItem : public FTableRowBase
{
	GENERATED_BODY()

public:

	FEquippedItem() {

	};

	FEquippedItem(const FGameplayTag& slot, const FInventoryItem& item) {
		ItemSlot = slot;
		InventoryItem = item;
	}

	UPROPERTY(SaveGame, BlueprintReadOnly, Category = ACF)
		FGameplayTag ItemSlot;

	UPROPERTY(SaveGame, BlueprintReadOnly, Category = ACF)
		FInventoryItem InventoryItem;

	FORCEINLINE	bool operator==(const FEquippedItem& Other) const
	{
		return this->ItemSlot == Other.ItemSlot;
	}

	FORCEINLINE	bool operator!=(const FEquippedItem& Other) const
	{
		return this->ItemSlot != Other.ItemSlot;
	}

	FORCEINLINE	bool operator==(const FGameplayTag& Other) const
	{
		return this->ItemSlot == Other;
	}

	FORCEINLINE	bool operator!=(const FGameplayTag& Other) const
	{
		return this->ItemSlot != Other;
	}

};

USTRUCT(BlueprintType)
struct FEquipment
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = ACF)
		class AACFWeapon* MainWeapon;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = ACF)
		class AACFWeapon* SecondaryWeapon;

	UPROPERTY(SaveGame, BlueprintReadOnly, Category = ACF)
	TArray<FEquippedItem> EquippedItems;

};

   
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnEquipmentChanged, const FEquipment&, Equipment);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnInventoryChanged, const TArray<FInventoryItem>&, Inventory);

UCLASS(Blueprintable, ClassGroup = (ACF), meta = (BlueprintSpawnableComponent))
class ASCENTCOMBATFRAMEWORK_API UACFEquipmentComponent : public UActorComponent
{
	GENERATED_BODY()

public:

	/*Adds the items referenced by the World Item to this Inventory */
	UFUNCTION(Server, WithValidation, Reliable, BlueprintCallable, Category = ACF)
	void AddWorldItemToInventory(class AACFWorldItem* ItemToAdd, const TArray<int>& ItemToPick);

	/*Adds the selected item to this Inventory */
	UFUNCTION(Server, WithValidation, Reliable, BlueprintCallable, Category = ACF)
	void AddItemToInventory( class AACFItem* ItemToAdd, uint8 count = 1);

	/*Moves the item at the provided from the Inventory to the Equipment*/
	UFUNCTION(Server, WithValidation, Reliable, BlueprintCallable, Category = ACF)
	void UseInventoryItem(int32 index);

	/*Moves the provided item from the Inventory to the Equipment*/
	UFUNCTION(Server, WithValidation, Reliable, BlueprintCallable, Category = ACF)
	void MoveItemToEquipment(const class AACFItem* item);

	/*Removes the selected amount of the provided item from the inventory and Unequips it 
	if it is equipped*/
	UFUNCTION(Server, WithValidation, Reliable, BlueprintCallable, Category = ACF)
	void RemoveItem(const class AACFItem* item, uint8 count = 1);

	/*Removes the selected amount of the provided item from the inventory, Unequips it
	if it is equipped and spawn a WorldItem near the owner position  containing the selectede items*/
	UFUNCTION(Server, WithValidation, Reliable, BlueprintCallable, Category = ACF)
	void DropItem(const class AACFItem* item, uint8 count = 1);
	
	UFUNCTION(BlueprintCallable, Category = ACF)
	bool HasEnoughItemsOfType(const TArray<FBaseItem>& ItemsToCheck);

	UFUNCTION(Server, WithValidation, Reliable, BlueprintCallable, Category = ACF)
	void ConsumeItems(const TArray<FBaseItem>& ItemsToCheck);
	
	// Sets default values for this component's properties
	UACFEquipmentComponent();

	
	UFUNCTION(Server, WithValidation, Reliable, BlueprintCallable, Category = ACF)
	void EquipArmor( class AACFArmor* ArmorToEquip);

	UFUNCTION(BlueprintPure, Category = ACF)
	FORCEINLINE  AACFWeapon* GetCurrentMainWeapon() const { return Equipment.MainWeapon; }

	UFUNCTION(BlueprintPure, Category = ACF)
	FORCEINLINE  AACFWeapon* GetCurrentSecondaryWeapon() const { return Equipment.SecondaryWeapon; }

	UFUNCTION(BlueprintPure, Category = ACF)
	FORCEINLINE  FEquipment GetCurrentEquipment() const { return Equipment; }

	UFUNCTION(BlueprintPure, Category = ACF)
	FORCEINLINE  TArray<FInventoryItem> GetInventory() const { return Inventory; }

	/**	
	* Gets the Item equipped in a specific slot 
	* @param itemSlot: the slot requested
	* @param: outSlot: the character's item
	*/
	UFUNCTION(BlueprintCallable, Category = ACF)
	bool GetEquippedItemSlot( FGameplayTag itemSlot, FInventoryItem& outSlot) const;

	UFUNCTION(BlueprintCallable, Category = ACF)
	bool GetModularMesh( FGameplayTag  itemSlot, FModularPart& outMesh) const;

	UFUNCTION(BlueprintCallable, Category = ACF)
	bool HasAnyItemInEquipmentSlot(FGameplayTag itemSlor) const;

	/* Equips a weapon, if it is in the inventory */
	UFUNCTION(Server, WithValidation, Reliable, BlueprintCallable, Category = ACF)
	void EquipWeapon( class AACFWeapon* WeaponToEquip);

	/*Moves the provided consumable in the equipment, if it exist in the inventory*/
	UFUNCTION(Server, WithValidation, Reliable, BlueprintCallable, Category = ACF)
	void EquipConsumable(class AACFConsumable* itemToEquip);

	UFUNCTION(Server, WithValidation, Reliable, BlueprintCallable, Category = ACF)
	void EquipAccessory(class AACFAccessory* itemToEquip);

	UFUNCTION(Server, WithValidation, Reliable, BlueprintCallable, Category = ACF)
	void UnequipAccessory(FGameplayTag itemSlot);

	/* Use the item in the specified slot of the Equipment*/
	UFUNCTION(Server, WithValidation, Reliable, BlueprintCallable, Category = ACF)
	void UseItemBySlot(FGameplayTag itemSlot);

	UFUNCTION(Server, WithValidation, Reliable, BlueprintCallable, Category = ACF)
	void UnequipItemBySlot(FGameplayTag itemSlot);

	/*Removes the currently weapon in the hand of the character*/
	UFUNCTION(Server, WithValidation, Reliable, BlueprintCallable, Category = ACF)
	void SheathCurrentWeapon();

	/*Moves the Inventory Item to the Equipment*/
	UFUNCTION(Server, WithValidation, Reliable, BlueprintCallable, Category = ACF)
	void EquipItemFromInventory(const FInventoryItem& item);

	UFUNCTION(Server, WithValidation, Reliable, BlueprintCallable, Category = ACF)
	void DropItemFromInventory(const FInventoryItem& item, int32 count);

	UFUNCTION(Server, WithValidation, Reliable, BlueprintCallable, Category = ACF)
	void DropItemByInventoryIndex(int32 itemIndex, int32 count);

	UFUNCTION(BlueprintCallable, Category = ACF)
	void SetDamageActivation(bool isActive, bool isLeftWeapon = false);

	UFUNCTION(BlueprintPure, Category = ACF)
	bool CanSwitchToRanged();

	UFUNCTION(BlueprintPure, Category = ACF)
	bool CanSwitchToMelee();

	UFUNCTION(BlueprintPure, Category = ACF)
	float GetCurrentInventoryTotalWeight() const{
		return currentInventoryWeight;
	}

	UFUNCTION(BlueprintCallable, Category = ACF)
	bool HasOnBodyAnyWeaponOfType(TSubclassOf<AACFWeapon> weaponClass) const;

	/* Gets an item from the inventory by its GUID. Returns false if it is not present.*/
	UFUNCTION(BlueprintCallable, Category = ACF)
	bool GetInventoryItem(const class AACFItem* item, FInventoryItem& outItem);

	/* Use this only on Server!!!
	*
	*Initialize a character's inventory and equipment
	*/
	UFUNCTION(BlueprintCallable, Category = ACF)
	void InitializeInventoryAndEquipment();

	UFUNCTION(Server, WithValidation, Reliable, Category = ACF)
	void DestroyEquippedItems();

	UFUNCTION(Server, WithValidation, Reliable, BlueprintCallable, Category = ACF)
	void UnequipOnBodyWeapon(FGameplayTag Slot);

	/* If an armor is equipped, Unequip it*/
	UFUNCTION(BlueprintCallable, Category = ACF)
	void UnequipArmor(FGameplayTag itemSlot);

	virtual void BeginPlay() override;

	void RefreshEquipmentAttachments();

	TArray<FInventoryItem*> FindInInventoryByItemClass(AACFItem* item);
	
	TArray<FInventoryItem*> FindItemsByClass(TSubclassOf<AACFItem> itemToFind);

	UPROPERTY(BlueprintAssignable, Category = ACF)
	FOnEquipmentChanged OnEquipmentChanged;

	UPROPERTY(BlueprintAssignable, Category = ACF)
	FOnInventoryChanged OnInventoryChanged;

	
	//addition code
	UFUNCTION(BlueprintPure,Category = ACF)
	FORCEINLINE TArray<FModularPart> GetModularMeshes() const{return ModularMeshes;}

	
protected:
	/* Slots available to the character*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = ACF)
	TArray<FGameplayTag> AvailableItemsSlot;

	/*Defines if the Entity should drop all his droppable invnentory Items when it dies*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ACF)
	bool bDropItemsOnDeath = true;

	/* the character's mesh pointer*/
	UPROPERTY(BlueprintReadOnly, Category = ACF)
	USkeletalMeshComponent*  MainCharacterMesh;

	/*Maximum number of Slot items in Inventory*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ACF)
	uint8 MaxInventorySlots = 8;

	/*Define if an item should be automatically Equipped On Body, if it is picked up from world */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ACF)
	bool bAutoEquipItem = true;

	/*Max cumulative weight on*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ACF)
	float MaxInventoryWeight = 80.f;

	/* The character's starting items*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ACF)
	TArray<FStatingItem> StartingItems;

private: 
	/*Inventory of this character*/
	UPROPERTY(SaveGame, Replicated, ReplicatedUsing = OnRep_Inventory)
	TArray<FInventoryItem> Inventory;

	//UFUNCTION(BlueprintCallable)
	FInventoryItem* Internal_GetInventoryItem(const AACFItem* itemToSearch);

	UFUNCTION()
	void OnRep_Equipment();

	UFUNCTION()
	void OnRep_Inventory();

	UFUNCTION()
	void OnEntityOwnerDeath();

	UPROPERTY(SaveGame, Replicated, ReplicatedUsing = OnRep_Equipment)
	FEquipment Equipment;

	UPROPERTY()
	class AACFCharacter* CharacterOwner;

	UPROPERTY()
	class USkeletalMesh* _characterBaseMesh;

	UPROPERTY()
	TArray<FModularPart> ModularMeshes;

	UPROPERTY()
	FGameplayTag _desiredSlot;

	UPROPERTY(Replicated)
	FGameplayTag CurrentlyEquippedSlotType;

	UPROPERTY(Replicated)
	float currentInventoryWeight = 0.f;

	/* Unequips the item if it is a Weapon, Armor or Consumable and it is currently equipped*/
	void RemoveItemFromEquipment( FInventoryItem& item);
	
	void UnequipConsumable(FGameplayTag Slot);

	void MarkItemOnInventoryAsEquipped(const class AACFItem* item, bool bIsEquipped);

	void RemoveEquippedBySlot(const FGameplayTag& slot);

	bool CanBeEquipped(const class AACFItem* equippable);


	uint8 Internal_AddItem(AACFItem* itemToAdd, uint8 count);


	void AttachWeaponOnBody(AACFWeapon* WeaponToEquip);

	void AttachWeaponOnHand(AACFWeapon* _localWeapon);

	uint8 AddItemToInventoryByClass(TSubclassOf<AACFItem> itemClass, uint8 count = 1, bool bTryToEquip = true, float dropChance = 0.f);

	bool AddSkeletalMeshComponent(AACFArmor* ArmorToAdd);

	void SpawnWorldItem(uint8 count, TSubclassOf<AACFItem> item);


public:
	//my addition code
	/*Move a item from one EquipmentComponent to another,usually used for a storage*/
	UFUNCTION(Server, WithValidation, Reliable, BlueprintCallable, Category = ACF)
	void MoveItemToAnotherInventory(UACFEquipmentComponent* OtherEquipmentComponent,class AACFItem* itemToMove, uint8 count = 1);

	UFUNCTION(BlueprintCallable, Category = ACF)
	int NumberOfItemCanTake(AACFItem* itemToCheck);

	UFUNCTION(BlueprintPure, Category = ACF)
	FORCEINLINE int GetMaxInventorySlots()const{return MaxInventorySlots;}

	UFUNCTION(BlueprintPure, Category = ACF)
	FORCEINLINE int GetMaxInventoryWeight()const{return MaxInventoryWeight;}
};
