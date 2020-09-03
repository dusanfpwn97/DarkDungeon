// Copyright (C) Pakyman Prod. 2020. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Items/ACFItem.h"
#include "ARSStatisticsData.h"
#include <Components/SkeletalMeshComponent.h>
#include "ACFEquippableItem.generated.h"

/**
 * 
 */


UCLASS()
class ASCENTCOMBATFRAMEWORK_API AACFEquippableItem : public AACFItem
{
	GENERATED_BODY()

public:

	friend class UACFEquipmentComponent;

	AACFEquippableItem();

	/*Modifier applied once this item is equipped*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ACF | Equippable")
	FAttributesSetModifier AttributeModifier;

	/*Attributes requirement to equip this item*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ACF | Equippable")
	TArray<FAttribute> PrimaryAttributesRequirement;

	UFUNCTION(BlueprintCallable, Category = ACF)
	FORCEINLINE class USkeletalMeshComponent* GetMeshComponent() const { return Mesh; };

	/*Played when equipped*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "ACF | Equippable")
	class USoundCue* EquipSound;

	/*Played when unequipped*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "ACF | Equippable")
	class USoundCue* UnequipSound;


protected:

	void RemoveModifierToOwner(FAttributesSetModifier _attributeModifier);
	void AddModifierToOwner(FAttributesSetModifier _attributeModifier);

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = ACF)
	class USkeletalMeshComponent* Mesh;

	UFUNCTION(BlueprintNativeEvent, Category = ACF)
	void OnItemEquipped();
	virtual void OnItemEquipped_Implementation();
		
			
	UFUNCTION(BlueprintNativeEvent, Category = ACF)
	void OnItemUnEquipped();
	virtual void OnItemUnEquipped_Implementation();

private: 

	UFUNCTION()
	void Internal_OnEquipped(class AACFCharacter* _owner);

	UFUNCTION()
	void Internal_OnUnEquipped();
};
