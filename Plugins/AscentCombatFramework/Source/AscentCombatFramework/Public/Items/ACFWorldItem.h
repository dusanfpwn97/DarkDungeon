// Copyright (C) Pakyman Prod. 2020. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Items/ACFItem.h"
#include "Interfaces/ACFInteractableInterface.h"
#include "Components/ACFEquipmentComponent.h"
#include "Interfaces/ACFSavableInterface.h"
#include "ACFWorldItem.generated.h"


/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnWorldItemChanged, const TArray<FBaseItem>&, RemainingItems);


UCLASS()
class ASCENTCOMBATFRAMEWORK_API AACFWorldItem : public AActor, public IACFInteractableInterface, public IACFSavableInterface
{
	GENERATED_BODY()

public:

	AACFWorldItem();

	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable, Category = ACF)
	void SetItemsArray(const TArray<FBaseItem>& inItems);

	UFUNCTION(Server, WithValidation, Reliable, Category = ACF)
	void RemoveItems(const TArray<FBaseItem>& inItems);

	/* called when player interact with object of this class */
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = ACF)
	void OnInteractedByPawn(class APawn* Pawn);
	virtual void OnInteractedByPawn_Implementation(class APawn* Pawn) override;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = ACF)
	void OnInteractableRegisteredByPawn(class APawn* Pawn);
	virtual void OnInteractableRegisteredByPawn_Implementation(class APawn* Pawn) override;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = ACF)
	void  OnInteractableUnregisteredByPawn(class APawn* Pawn);
	virtual void OnInteractableUnregisteredByPawn_Implementation(class APawn* Pawn) override;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = ACF)
	bool CanBeInteracted(class APawn* Pawn);
	virtual bool CanBeInteracted_Implementation(class APawn* Pawn) override;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = ACF)
	FText GetInteractableName();
	virtual FText GetInteractableName_Implementation() override;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = ACF)
	void OnActorLoaded();
	virtual void OnActorLoaded_Implementation() override;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = ACF)
		void OnActorSaved();
	virtual void OnActorSaved_Implementation() override;

	/*Return the items related to this world Item*/
	UFUNCTION(BlueprintPure, Category = ACF)
	FORCEINLINE TArray<FBaseItem> GetItems() const {return  Items; }

	/* Get the Item descriptor */
	UFUNCTION(BlueprintPure, Category = ACF)
	FORCEINLINE FItemDescriptor GetFirstItemInfo() const{ return  ItemInfo; }

	/* Destroy this actor when all items are gathered */
	UFUNCTION(BlueprintPure, Category = ACF)
	FORCEINLINE bool DestroyOnAllItemsGathered() const { return  bDestroyOnGather; }
	
	/*Create and Inventory Item*/
	UFUNCTION(BlueprintPure, Category = ACF)
	void ConstructInventoryItems(TArray<FInventoryItem>& outItems);

	UPROPERTY(BlueprintAssignable, Category = ACF)
	FOnWorldItemChanged OnWorldItemChanged;

	UFUNCTION(Server, WithValidation, Reliable, Category = ACF)
	void RemoveItemsByIndex(const TArray<FBaseItem>& inItems);

protected: 
	//changed
	UPROPERTY(EditAnywhere, BlueprintReadWrite, SaveGame, ReplicatedUsing = OnRep_Items, Category = ACF)
	TArray<FBaseItem> Items;	

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ACF)
	bool bDestroyOnGather = true;

	/* Mesh to be displayed */
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = ACF)
	class UStaticMeshComponent* ObjectMesh;


	UPROPERTY(BlueprintReadOnly, Category = ACF)
	FItemDescriptor ItemInfo;
	//addition code
	UFUNCTION()
	void OnRep_Items();

private: 

};
