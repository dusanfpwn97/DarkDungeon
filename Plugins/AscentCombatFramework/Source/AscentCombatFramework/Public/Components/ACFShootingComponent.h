// Copyright (C) Pakyman Prod. 2020. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Items/ACFWeapon.h"
#include <Components/MeshComponent.h>
#include "ACFShootingComponent.generated.h"


UCLASS(Blueprintable, ClassGroup = (ACF), meta = (BlueprintSpawnableComponent))
class ASCENTCOMBATFRAMEWORK_API UACFShootingComponent : public UActorComponent
{
	GENERATED_BODY()



protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = "ACF")
	TSubclassOf<class AACFProjectile> ProjectileClassBP;

	UPROPERTY(EditDefaultsOnly, Category = "ACF" )
	FName ProjectileStartSocket = "ProjectileStart";

	UPROPERTY(EditDefaultsOnly, Category = "ACF")
	FWeaponEffects ShootingEffect;
	
	/*Speed at wich the projectile is shot*/
	UPROPERTY(EditAnywhere, Category = "ACF")
	float ProjectileShotSpeed;

	UPROPERTY(EditAnywhere, Category = "ACF")
	float ProjectileMaxSpeed;



private:
	UPROPERTY()
	UMeshComponent* shootingMesh;

	UPROPERTY()
	AACFCharacter* characterOwner;

	void Internal_Shoot(const FTransform& spawnTransform, const FVector& ShotDirection, float charge, TSubclassOf<class AACFProjectile> inProjClass);

public:
	// Sets default values for this component's properties
	UACFShootingComponent();

	UFUNCTION(BlueprintCallable, Category = ACF)
	void SetupShootingComponent(class AACFCharacter* inOwner, class UMeshComponent* inMesh) {
		shootingMesh = inMesh;
		characterOwner = inOwner;
	}

	UFUNCTION(BlueprintPure, Category = ACF)
		FORCEINLINE float GetProjectileSpeed() const { return ProjectileShotSpeed; }

	UFUNCTION(BlueprintCallable, Category = ACF)
		void ShootAtActor(const AActor* target, float randomDeviation = 5.f, float charge = 1.f, TSubclassOf<class AACFProjectile> projectileOverride = nullptr);

	UFUNCTION(BlueprintCallable, Category = ACF)
		void ShootAtDirection(const FRotator& direction, float charge = 1.f, TSubclassOf<class AACFProjectile> projectileOverride = nullptr);

	UFUNCTION(BlueprintPure, Category = ACF)
		FORCEINLINE float GetShootingSpeed() const {
		return ProjectileShotSpeed;
	}

	UFUNCTION(BlueprintPure, Category = ACF)
		FORCEINLINE UMeshComponent* GetShootingMesh() const {
		return shootingMesh;
	}
};
