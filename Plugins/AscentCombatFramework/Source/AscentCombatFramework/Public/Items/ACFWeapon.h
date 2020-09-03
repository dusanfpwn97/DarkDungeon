// Copyright (C) Pakyman Prod. 2020. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Items/ACFEquippableItem.h"
#include "ACFWeapon.generated.h"

/**
 * 
 */

USTRUCT(BlueprintType)
struct FWeaponEffects : public FTableRowBase
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = ACF)
		class USoundCue* AttackSound;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = ACF)
		class UParticleSystem* AttackParticle;

};

UCLASS()
class ASCENTCOMBATFRAMEWORK_API AACFWeapon : public AACFEquippableItem
{
	GENERATED_BODY()

public:

	friend class UACFEquipmentComponent;

	AACFWeapon();
	
	UFUNCTION(BlueprintPure, Category = ACF)
	FORCEINLINE FGameplayTag GetWeaponType() const { return WeaponType; }

	UFUNCTION(BlueprintPure, Category = ACF)
	FORCEINLINE FGameplayTag GetAssociatedMovesetTag() const { return Moveset; }

	UFUNCTION(BlueprintPure, Category = ACF)
	FORCEINLINE FGameplayTag GetAssociatedMovesetActionsTag() const { return MovesetActions; }

	UFUNCTION(BlueprintPure, Category = ACF)
	FORCEINLINE FGameplayTag GetAssociatedMovesetOverlayTag() const { return MovesetOverlay; }

	UFUNCTION(BlueprintPure, Category = ACF)
	FORCEINLINE FName GetOnBodySocketName() const { return OnBodySocketName; }

	UFUNCTION(BlueprintPure, Category = ACF)
	FORCEINLINE FName GetEquippedSocketName() const { return EquippedSocketName; }


protected:

	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadOnly, EditAnyWhere, Category = "ACF | Weapon")
	class USceneComponent* HandlePos;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "ACF | Weapon")
	TSubclassOf<AACFWeapon> LeftHandWeaponClass;

	virtual void OnItemEquipped_Implementation() override;

	virtual void OnItemUnEquipped_Implementation() override;

	/*Tag identifying the actual weapontype*/
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "ACF | Weapon")
	FTransform AttachmentOffset ;

	/*Tag identifying the actual weapontype*/
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "ACF | Weapon")
	FGameplayTag WeaponType;

	/*Once this weapon is equipped, the equipping character will try to switch to this moveset*/
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "ACF | Weapon")
	FGameplayTag Moveset;

	/*Once this weapon is equipped, the equipping character will try to add this overlay*/
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "ACF | Weapon")
	FGameplayTag MovesetOverlay;

	/*Once this weapon is equipped, those are the actions that can be triggered*/
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "ACF | Weapon")
	FGameplayTag MovesetActions;

	/*Socket in which this weapon will be attached once it is equipped on the back of the character*/
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "ACF | Weapon")
	FName OnBodySocketName;

	/*Socket in which this weapon will be attached once it is unsheathed*/
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "ACF | Weapon")
	FName EquippedSocketName;

	UPROPERTY()
	FGameplayTag CurrentEnchantment;

private:
	void AlignWeapon();
	
	UPROPERTY()
	AACFWeapon* LeftHandWeapon;
};
