// Copyright (C) Pakyman Prod. 2020. All Rights Reserved.

#include "Items/ACFWeapon.h"
#include <GameFramework/DamageType.h>
#include <Components/SceneComponent.h>

AACFWeapon::AACFWeapon()
{
	SetReplicates(true);
	HandlePos = CreateDefaultSubobject<USceneComponent>(TEXT("Handle"));
	SetRootComponent(HandlePos);
	//	Root = CreateDefaultSubobject<USceneComponent>(TEXT("RootComp"));
		//ItemInfo.ItemType = EItemType::MeleeWeapon;

	Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}


void AACFWeapon::BeginPlay()
{
	Super::BeginPlay();
	Mesh->AttachToComponent(HandlePos, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, false));
	AlignWeapon();

	UWorld* world = GetWorld();
	if (LeftHandWeaponClass && !LeftHandWeapon)
	{
		LeftHandWeapon = Cast<AACFWeapon>(world->SpawnActor(LeftHandWeaponClass));
		LeftHandWeapon->SetActorHiddenInGame(true);
	}
	
}

void AACFWeapon::OnItemEquipped_Implementation()
{
	Super::OnItemEquipped_Implementation();
	AlignWeapon();
}

void AACFWeapon::OnItemUnEquipped_Implementation()
{
	Super::OnItemUnEquipped_Implementation();
	AlignWeapon();
}

void AACFWeapon::AlignWeapon()
{	
	if (HandlePos)
	{
		FHitResult outResult;
		Mesh->SetRelativeTransform(AttachmentOffset, true, &outResult, ETeleportType::TeleportPhysics);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("NO HANDLE COMPONENT! - ACFWeapon"));
	}
}


