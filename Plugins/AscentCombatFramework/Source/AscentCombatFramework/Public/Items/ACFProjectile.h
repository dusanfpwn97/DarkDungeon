// Copyright (C) Pakyman Prod. 2020. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ACFItem.h"
#include <Components/StaticMeshComponent.h>
#include "ACFProjectile.generated.h"

UCLASS()
class ASCENTCOMBATFRAMEWORK_API AACFProjectile : public AACFItem
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AACFProjectile();

	UFUNCTION(BlueprintPure, Category = ACF)
	FORCEINLINE class UProjectileMovementComponent* GetProjectileMovementComp() { return ProjectileMovementComp;  }

	UFUNCTION(BlueprintPure, Category = ACF)
	FORCEINLINE class UStaticMesh* GetStaticMesh() { return MeshComp->GetStaticMesh(); }

	UFUNCTION(BlueprintPure, Category = ACF)
	FORCEINLINE class UStaticMeshComponent* GetMeshComponent() const { return MeshComp; };

	UFUNCTION(BlueprintPure, Category = ACF)
	FORCEINLINE class UACMCollisionManagerComponent* GetCollisionComp() const { return CollisionComp; }

	UFUNCTION(BlueprintCallable, Category = ACF)
	void SetupProjectile(class AACFCharacter* inOwner, float launchSpeed);

	UFUNCTION(BlueprintCallable, Category = ACF)
	void ActivateDamage();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class USceneComponent* RootComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class UStaticMeshComponent* MeshComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class UProjectileMovementComponent* ProjectileMovementComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class UACMCollisionManagerComponent* CollisionComp;

	/* If this projectile must remain attached to the body of the character hit*/
	UPROPERTY(EditDefaultsOnly, Category = "ACF | Projectile")
	bool bAttachOnHit = true;

	/* How deep this projectile must penetrate  the body of the character hit*/
	UPROPERTY(EditDefaultsOnly,  Category = "ACF | Projectile")
	float PenetrationLevel = 30.f;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "ACF | Projectile")
	float ProjectileLifespan = 5.f;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "ACF | Projectile")
	float AttachedLifespan = 10.f;

	

private:
	
	bool bIsFlying;

	void MakeStatic();

	UFUNCTION()
	void HandleAttackHit(FName TraceName, const FHitResult& HitResult);


};
