// Copyright (C) Pakyman Prod. 2020. All Rights Reserved.

#include "Items/ACFProjectile.h"
#include <GameFramework/ProjectileMovementComponent.h>
#include <Engine/EngineTypes.h>
#include <Components/StaticMeshComponent.h>
#include <Components/SceneComponent.h>
#include "Game/ACFDamageType.h"
#include "ACMCollisionManagerComponent.h"
#include "Items/ACFRangedWeapon.h"
#include "Actors/ACFCharacter.h"
#include <Kismet/GameplayStatics.h>
#include <Particles/ParticleSystemComponent.h>
#include <GameFramework/Actor.h>


// Sets default values
AACFProjectile::AACFProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	// Create A Default Root Component as a container
	RootComp = CreateDefaultSubobject<USceneComponent>(TEXT("RootComp"));
	RootComponent = RootComp;

	CollisionComp = CreateDefaultSubobject<UACMCollisionManagerComponent>(TEXT("Collision Manager Comp"));
	// Attach Mesh component to root component
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ProjectileMeshComp"));
	MeshComp->SetupAttachment(RootComp);
	MeshComp->SetCollisionProfileName(TEXT("NoCollision"));
	MeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	SetReplicates(true);
	SetReplicateMovement(true);
	ItemInfo.Name = FText::FromString("Base Projectile");
	// Use a ProjectileMovementComponent to govern this projectile's movement
	ProjectileMovementComp = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComp"));


	ProjectileMovementComp->UpdatedComponent = RootComp;
	ProjectileMovementComp->InitialSpeed = 3000.f;
	ProjectileMovementComp->MaxSpeed = 4000.0f;
	ProjectileMovementComp->bRotationFollowsVelocity = true;
	ProjectileMovementComp->bShouldBounce = false;
	ProjectileMovementComp->bAutoActivate = false;
	
	bIsFlying = false;
	//ItemType = EItemType::Projectile;
	//PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void AACFProjectile::BeginPlay()
{
	Super::BeginPlay();

	if (!bIsFlying)
	{
		MakeStatic();
		SetLifeSpan(AttachedLifespan);
	}
	else
	{
		ProjectileMovementComp->SetActive(true);
		SetLifeSpan(ProjectileLifespan);
;	}	
}

void AACFProjectile::SetupProjectile(class AACFCharacter* inOwner, float launchSpeed)
{
	if (inOwner){
		bIsFlying = true;
		ItemOwner = inOwner;
		if (ProjectileMovementComp)		{
			ProjectileMovementComp->MaxSpeed = launchSpeed;
		}
	}
	else{
		bIsFlying = false;
	}
}

void AACFProjectile::ActivateDamage()
{
	AACFCharacter* characterOwner = Cast<AACFCharacter>(ItemOwner);
	if (CollisionComp)
	{
		/*	CollisionComp->AddActorToIgnore(ItemOwner);*/
		CollisionComp->SetActorOwner(ItemOwner);
		CollisionComp->SetupCollisionManager(MeshComp);
		TArray<TEnumAsByte<ECollisionChannel>> channels = characterOwner->GetEnemiesCollisionChannel();
		for (auto chan : channels) {
			CollisionComp->AddCollisionChannel(chan);
		}

		CollisionComp->StartAllTraces();
		CollisionComp->OnCollisionDetected.AddDynamic(this, &AACFProjectile::HandleAttackHit);
	}
}

void AACFProjectile::MakeStatic()
{
	ProjectileMovementComp->SetActive(false);
	ProjectileMovementComp->Velocity = FVector::ZeroVector;
	SetActorScale3D(FVector(1.0f, 1.0f, 1.0f));
}

void AACFProjectile::HandleAttackHit(FName TraceName, const FHitResult& HitResult)
{
	AACFCharacter* _damagedActor = Cast<AACFCharacter>(HitResult.Actor);

	if (ItemOwner && _damagedActor)
	{			
		ItemOwner->OnDamageInflicted.Broadcast(_damagedActor);
	}
	
	if (bAttachOnHit)// &&  HitResult.BoneName != NAME_None)
	{
		//_damagedActor->GetMesh()->GetBoneLocation(HitResult.BoneName);//
		FVector AttachLocation = GetActorLocation() + (GetActorForwardVector() * PenetrationLevel);
		FActorSpawnParameters spawnParam;
		spawnParam.Owner = _damagedActor;
		spawnParam.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		AACFProjectile* copyProjectile =
			GetWorld()->SpawnActor<AACFProjectile>(this->GetClass(), AttachLocation, GetActorRotation(), spawnParam);
		FAttachmentTransformRules rule = FAttachmentTransformRules::SnapToTargetNotIncludingScale;
		if(_damagedActor )			
		{
			copyProjectile->AttachToComponent(_damagedActor->GetMesh(), rule, HitResult.BoneName);
		}
		else
		{
			copyProjectile->AttachToComponent(HitResult.Component.Get(), rule);
		}
		copyProjectile->SetActorRotation(GetActorRotation());
		CollisionComp->StopAllTraces();
		Destroy();

	}
}

