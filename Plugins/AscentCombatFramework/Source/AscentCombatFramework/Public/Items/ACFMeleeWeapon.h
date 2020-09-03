// Copyright (C) Pakyman Prod. 2020. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Items/ACFWeapon.h"
#include <GameplayTagContainer.h>
#include "ACFMeleeWeapon.generated.h"

/**
 * 
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnWeaponHit, FHitResult, HitResult);



UCLASS()
class ASCENTCOMBATFRAMEWORK_API AACFMeleeWeapon : public AACFWeapon
{
	GENERATED_BODY()

public:

	AACFMeleeWeapon();

	virtual void BeginPlay() override;

	UPROPERTY(BlueprintAssignable, Category = ACF)
	FOnWeaponHit OnWeaponHit;

	UFUNCTION(BlueprintCallable, Category = ACF)
	void StartWeaponSwing();

	UFUNCTION(BlueprintCallable, Category = ACF)
	void StopWeaponSwing();


protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = ACF)
	class UACMCollisionManagerComponent* CollisionComp;


	virtual void OnItemEquipped_Implementation() override;

	virtual void OnItemUnEquipped_Implementation() override;

private:

	UFUNCTION()
	void HandleAttackHit(FName TraceName, const FHitResult& HitResult);

	UPROPERTY()
	float VFXCylinderHeight;

};
