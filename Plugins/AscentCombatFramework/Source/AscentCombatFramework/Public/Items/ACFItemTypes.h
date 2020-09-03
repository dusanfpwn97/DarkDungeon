// Copyright (C) Pakyman Prod. 2020. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include <GameplayTagContainer.h>
#include "ACFItemTypes.generated.h"

/**
 * 
 */

UENUM(BlueprintType)
enum class EItemType : uint8
{
	Armor = 0                UMETA(DisplayName = "Armor"),
	MeleeWeapon = 1          UMETA(DisplayName = "Melee Weapon"),
	RangedWeapon = 2         UMETA(DisplayName = "RangedWeapon"),
	Consumable = 3			 UMETA(DisplayName = "Consumable"),
	Material = 4			 UMETA(DisplayName = "Material"),
	Accessory = 5			 UMETA(DisplayName = "Accessory"),
	Other = 6			     UMETA(DisplayName = "Other"),
};





USTRUCT(BlueprintType)
struct FModularPart
{
	GENERATED_BODY()

public:

	FModularPart() {};

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = ACF)
		FGameplayTag ItemSlot;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = ACF)
		class USkeletalMeshComponent* meshComp;

	FORCEINLINE	bool operator==(const FModularPart& Other) const
	{
		return this->ItemSlot == Other.ItemSlot;
	}

	FORCEINLINE	bool operator!=(const FModularPart& Other) const
	{
		return this->ItemSlot != Other.ItemSlot;
	}

	FORCEINLINE	bool operator!=(const FGameplayTag& Other) const
	{
		return this->ItemSlot != Other;
	}

	FORCEINLINE	bool operator==(const FGameplayTag& Other) const
	{
		return this->ItemSlot == Other;
	}

};






UCLASS()
class ASCENTCOMBATFRAMEWORK_API UACFItemTypes : public UObject
{
	GENERATED_BODY()
	
};
