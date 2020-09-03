// Copyright (C) Pakyman Prod. 2020. All Rights Reserved.


#include "Components/ACFShootingComponent.h"
#include <Kismet/GameplayStatics.h>
#include "Items/ACFProjectile.h"
#include <Engine/World.h>
#include <Sound/SoundCue.h>
#include <GameFramework/ProjectileMovementComponent.h>
#include "Game/ACFDamageType.h"

// Sets default values for this component's properties
UACFShootingComponent::UACFShootingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
	ProjectileShotSpeed = 1000.0f;
	ProjectileMaxSpeed = 3500.0f;
	//ShootingEffect.DamageType = URangedDamageType::StaticClass();
}


// Called when the game starts
void UACFShootingComponent::BeginPlay()
{
	Super::BeginPlay();	
}


void UACFShootingComponent::ShootAtDirection(const FRotator& direction, float charge /*= 1.f*/, TSubclassOf<class AACFProjectile> projectileOverride)
{

	if (!(shootingMesh && characterOwner)) {
		UE_LOG(LogTemp, Error, TEXT("Shooting component not initialized! - UACFShootingComponent::Internal_Shoot"));
		return;
	}

	FVector ShotDirection = direction.Vector();

	FTransform spawnTransform;
	spawnTransform.SetLocation(shootingMesh->GetSocketLocation(ProjectileStartSocket));
	spawnTransform.SetRotation(direction.Quaternion());
	spawnTransform.SetScale3D(FVector(1.f, 1.f, 1.f));

	Internal_Shoot(spawnTransform, ShotDirection, charge, projectileOverride);
}

void UACFShootingComponent::ShootAtActor(const AActor* target, float randomDeviation /*= 50.f*/, float charge /*= 1.f*/, TSubclassOf<class AACFProjectile> projectileOverride)
{

	if (!(shootingMesh && characterOwner)) {
		UE_LOG(LogTemp, Error, TEXT("Shooting component not initialized! - UACFShootingComponent::Internal_Shoot"));
		return;
	}

	UWorld* world = GetWorld();

	if ( target && ProjectileClassBP)
	{
		FVector SpawnProjectileLocation = shootingMesh->GetSocketLocation(ProjectileStartSocket);
		FRotator ProjectileOrientation = shootingMesh->GetSocketRotation(ProjectileStartSocket);


		FVector targetLocation = target->GetActorLocation();

		FVector FlyDir;
		float FlyDistance;
		(targetLocation - SpawnProjectileLocation).ToDirectionAndLength(FlyDir, FlyDistance);
		float FlyTime = FlyDistance / ProjectileShotSpeed;
		FVector PredictedPosition = targetLocation + (target->GetVelocity() * FlyTime);

		float RandomOffset_z = FMath::RandRange(-randomDeviation, randomDeviation);
		float RandomOffset_x = FMath::RandRange(-randomDeviation, randomDeviation);
		float RandomOffset_y = FMath::RandRange(-randomDeviation, randomDeviation);

		// Override Predicted Location with offset value
		PredictedPosition += FVector(RandomOffset_x, RandomOffset_y, RandomOffset_z);

		// Finalize Projectile fly direction
		FlyDir = (PredictedPosition - SpawnProjectileLocation).GetSafeNormal();

		FTransform spawnTransform;
		spawnTransform.SetLocation(SpawnProjectileLocation);
		spawnTransform.SetRotation(ProjectileOrientation.Quaternion());

		Internal_Shoot(spawnTransform, FlyDir, charge, projectileOverride);
		
	}

}
void UACFShootingComponent::Internal_Shoot(const FTransform& spawnTransform, const FVector& ShotDirection, float charge, TSubclassOf<class AACFProjectile> projectileOverride)
{

	if (!(shootingMesh && characterOwner)) {
		UE_LOG(LogTemp, Error, TEXT("Shooting component not initialized! - UACFShootingComponent::Internal_Shoot"));
		return;
	}

	if (!ProjectileClassBP && ! projectileOverride) {
		UE_LOG(LogTemp, Error, TEXT("Please set a projectile class! - UACFShootingComponent::Internal_Shoot"));
		return;
	}

	TSubclassOf<class AACFProjectile> projToSpawn = projectileOverride ? projectileOverride : ProjectileClassBP;
	UWorld* world = GetWorld();
	AACFProjectile* projectile =
		world->SpawnActorDeferred<AACFProjectile>(projToSpawn,
			spawnTransform, nullptr, nullptr, ESpawnActorCollisionHandlingMethod::AlwaysSpawn);

	projectile->SetupProjectile(characterOwner, ProjectileMaxSpeed);
	projectile->FinishSpawning(spawnTransform);
	projectile->ActivateDamage();
	if (projectile)	{
		const FVector MuzzleLocation = shootingMesh->GetSocketLocation(ProjectileStartSocket);
		projectile->GetProjectileMovementComp()->Velocity = ShotDirection * ProjectileShotSpeed * charge;
	
		if (ShootingEffect.AttackSound)	{
			UGameplayStatics::PlaySoundAtLocation(this, ShootingEffect.AttackSound, MuzzleLocation);
		}

		if (ShootingEffect.AttackParticle)		{
			UGameplayStatics::SpawnEmitterAtLocation(this, ShootingEffect.AttackParticle, MuzzleLocation);
		}


	}
}

