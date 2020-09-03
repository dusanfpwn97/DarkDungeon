// Copyright (C) Pakyman Prod. 2020. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "ACFItem.h"
#include "ARSStatisticsData.h"
#include "Game/ACFData.h"
#include "ACFConsumable.generated.h"

/**
 * 
 */



UCLASS()
class ASCENTCOMBATFRAMEWORK_API AACFConsumable : public AACFItem
{
	GENERATED_BODY()

	AACFConsumable();

	friend class UACFEquipmentComponent;
protected: 
   
	UFUNCTION(BlueprintNativeEvent, Category = ACF)
	void OnItemUsed();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "ACF | Consumable")
	TArray<FStatisticModifier> StatModifier;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "ACF | Consumable")
	TArray<FTimedAttributeSetModifier> TimedAttributeSetModifier;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "ACF | Consumable")
	FEffect OnUsedEffect;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "ACF | Consumable")
	bool bConsumeOnUse = true;

private: 

	void Internal_UseItem(class AACFCharacter* owner);

};
