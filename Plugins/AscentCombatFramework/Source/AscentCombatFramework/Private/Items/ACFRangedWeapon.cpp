// Copyright (C) Pakyman Prod. 2020. All Rights Reserved.

#include "Items/ACFRangedWeapon.h"
#include "Items/ACFItem.h"
#include "Actors/ACFCharacter.h"
#include "Items/ACFProjectile.h"
#include <Kismet/GameplayStatics.h>
#include <Sound/SoundCue.h>
#include <GameFramework/ProjectileMovementComponent.h>
#include <Kismet/KismetMathLibrary.h>

AACFRangedWeapon::AACFRangedWeapon()
{
	
	ItemInfo.ItemType = EItemType::RangedWeapon;
	ItemInfo.Name = FText::FromString("Base Ranged Weapon");
	ShootingComp = CreateDefaultSubobject<UACFShootingComponent>(TEXT("ShotingComponent"));
}


void AACFRangedWeapon::BeginPlay()
{
	Super::BeginPlay();

}

// void AACFRangedWeapon::ConsumeAmmo()
// {
// 	if (bUseAmmo) {
// 		CurrentAmmo--;
// 	}
// }

void AACFRangedWeapon::Shoot(float charge /*= 1.f*/)
{	
	if (ItemOwner  && ShootingComp)
	{
		FVector EyesLocation;
		FRotator EyesRotation = ItemOwner->GetControlRotation();
	//	ItemOwner->GetActorEyesViewPoint(EyesLocation, EyesRotation);
	
		ShootingComp->ShootAtDirection(EyesRotation, charge);
	//	ConsumeAmmo();
	}
}

void AACFRangedWeapon::ShootAtDirection(const FRotator& direction, float charge /*= 1.f*/)
{
	if (ShootingComp) {
		ShootingComp->ShootAtDirection(direction, charge);
	}
}
/*
bool AACFRangedWeapon::CanShoot() const
{
	if (bUseAmmo) {
		return CurrentAmmo > 0;
	}
	return true;
}
*/
void AACFRangedWeapon::OnItemEquipped_Implementation()
{
	Super::OnItemEquipped_Implementation();
	if (ShootingComp) {
		ShootingComp->SetupShootingComponent(ItemOwner, Mesh);
	}
}

void AACFRangedWeapon::ShootAtActor(const AActor* target, float randomDeviation /*= 50.f*/, float charge /*= 1.f*/)
{
	if (ItemOwner && ShootingComp){
		ShootingComp->ShootAtActor(target, randomDeviation, charge);
	}
}




