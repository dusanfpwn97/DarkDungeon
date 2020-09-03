// Copyright (C) Pakyman Prod. 2020. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Items/ACFWeapon.h"
#include "Components/ACFShootingComponent.h"
#include "ACFRangedWeapon.generated.h"

/**
 * 
 */
UCLASS()
class ASCENTCOMBATFRAMEWORK_API AACFRangedWeapon : public AACFWeapon
{
	GENERATED_BODY()

public:

	AACFRangedWeapon();

	/*Shoots at owner's eyesight*/
	UFUNCTION(BlueprintCallable, Category = ACF)
	virtual void Shoot(float charge = 1.f);

	/*Shoots at the target actor*/
	UFUNCTION(BlueprintCallable, Category = ACF)
	virtual void ShootAtActor(const AActor* target, float randomDeviation = 5.f, float charge = 1.f);

	/*Shoots at the provided direction */
	UFUNCTION(BlueprintCallable, Category = ACF)
	void ShootAtDirection(const FRotator& direction, float charge = 1.f);

	UFUNCTION(BlueprintPure, Category = ACF)
	FORCEINLINE float GetProjectileSpeed() const { 
		return ShootingComp ? ShootingComp->GetShootingSpeed() : -1.f; }

	 void OnItemEquipped_Implementation() override;

// 	 UFUNCTION(BlueprintPure, Category = ACF)
// 	 bool CanShoot() const;

protected:

	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, Category = ACF)
	UACFShootingComponent* ShootingComp;
	/*
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = ACF)
	bool bUseAmmo = false;

	UPROPERTY(BlueprintReadOnly, meta = (EditCondition = "bUseAmmo"), Category = ACF)
	int32 CurrentAmmo;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (EditCondition = "bUseAmmo"), Category = ACF)
	int32 MaxAmmoInCharger; */

private: 

//	void ConsumeAmmo();
	
};
