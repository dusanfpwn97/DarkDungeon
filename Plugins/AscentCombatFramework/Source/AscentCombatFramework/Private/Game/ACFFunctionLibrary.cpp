// Copyright (C) Pakyman Prod. 2020. All Rights Reserved.

#include "Game/ACFFunctionLibrary.h"
#include <GameFramework/Actor.h>
#include <Kismet/KismetMathLibrary.h>
#include <GameplayTagContainer.h>
#include <Kismet/GameplayStatics.h>
#include "ACFDeveloperSettings.h"
#include <GameplayTagsManager.h>
#include "Actors/ACFCharacter.h"
#include <Components/AudioComponent.h>
#include <Sound/SoundCue.h>
#include "Items/ACFWorldItem.h"
#include "Game/ACFGameMode.h"
#include "Game/ACFGameState.h"
#include <Curves/CurveFloat.h>
#include "UI/ACFHUD.h"
#include <Engine/LevelStreaming.h>
#include <NavigationSystem.h>
#include "Game/ACFPlayerController.h"
#include "Game/ACFDamageCalculation.h"
#include "ACMCollisionManagerComponent.h"
#include <Engine/DataTable.h>
#include "Game/ACFDamageType.h"
#include "Components/ACFEffectsDispatcherComponent.h"


EDirection UACFFunctionLibrary::GetActorsRelativeDirection(const AActor* hitDealer, const AActor* receiver)
{
	if (!hitDealer || !receiver) {
		return EDirection::Back;
	}


	FVector damageDealerRelative = hitDealer->GetActorLocation()
		- receiver->GetActorLocation();

	FVector hitDir = damageDealerRelative.GetUnsafeNormal();

	float forwardDot = FVector::DotProduct(receiver->GetActorForwardVector(), hitDir);
	float rightDot = FVector::DotProduct(receiver->GetActorRightVector(), hitDir);
	if (forwardDot >= 0.707f)
		return EDirection::Front;
	else if (rightDot >= 0.707f)
		return EDirection::Right;
	else if (rightDot <= -0.707f)
		return EDirection::Left;
	else
		return EDirection::Back;
}

EDirection UACFFunctionLibrary::GetHitDirectionByHitResult(const AActor* hitDealer, const FHitResult& hitResult)
{
	ensure(hitDealer);

	AActor* receiver = hitResult.GetActor();

	return GetActorsRelativeDirection(hitDealer, receiver);

}


FVector UACFFunctionLibrary::GetActorsRelativeDirectionVector(const FACFDamageEvent& damageEvent)
{
	if (damageEvent.DamageDealer && damageEvent.DamageReceiver) {
		FVector damageDealerRelative = damageEvent.DamageReceiver->GetActorLocation() - damageEvent.DamageDealer->GetActorLocation() ;

		return damageDealerRelative.GetUnsafeNormal();
	}

	return FVector();
}


bool UACFFunctionLibrary::DoesDamageInvolveLocalPlayer(const FACFDamageEvent& damageEvent)
{
	if (!damageEvent.DamageDealer || !damageEvent.DamageReceiver) {
		return false;
	}
	AACFCharacter* localChar = GetLocalACFPlayerCharacter(damageEvent.DamageDealer);
	return damageEvent.DamageDealer == localChar || damageEvent.DamageReceiver == localChar;
}

FVector UACFFunctionLibrary::GetActorsOppositeRelativeDirection(const FACFDamageEvent& damageEvent)
{
	return -GetActorsRelativeDirectionVector(damageEvent);
}

FGameplayTag UACFFunctionLibrary::GetDefaultActionsState()
{
	UACFDeveloperSettings* settings = GetMutableDefault< UACFDeveloperSettings>();

	if (settings)
	{
		return settings->DefaultActionsState;
	}

	return FGameplayTag();

}

FGameplayTag UACFFunctionLibrary::GetDefaultDeathState()
{
	UACFDeveloperSettings* settings = GetMutableDefault< UACFDeveloperSettings>();

	if (settings)
	{
		return settings->DefaultDeathState;
	}

	return FGameplayTag();

}

FGameplayTag UACFFunctionLibrary::GetDefaultHitState()
{
	UACFDeveloperSettings* settings = GetMutableDefault< UACFDeveloperSettings>();

	if (settings)
	{
		return settings->DefaultHitState;
	}

	return FGameplayTag();

}

FGameplayTag UACFFunctionLibrary::GetHealthTag()
{
	UACFDeveloperSettings* settings = GetMutableDefault< UACFDeveloperSettings>();

	if (settings)
	{
		return settings->HealthTag;
	}

	return FGameplayTag();
}

float UACFFunctionLibrary::ApplyRandomDeviationToDamage(float Damage)
{
	UACFDeveloperSettings* settings = GetMutableDefault< UACFDeveloperSettings>();

	if (settings)
	{
		float _deviation = Damage * settings->DefaultRandomDamageDeviationPercentage / 100;
		return FMath::FRandRange(Damage - _deviation, Damage + _deviation);
	}

	return Damage;
}

float UACFFunctionLibrary::ReduceDamageByPercentage(float Damage, float Percentage)
{
	float _deviation = Damage * Percentage / 100 ;
	return Damage - _deviation;
}

float UACFFunctionLibrary::GetDamageMultiplierByDamageZone(EDamageZone DamagedZone)
{
	UACFDeveloperSettings* settings = GetMutableDefault< UACFDeveloperSettings>();

	if (settings)
	{
		float* _mult = settings->DamageZoneToDamageMultiplier.Find(DamagedZone);
		if (_mult)
		{
			return *_mult;
		}		
	}
	return 1.f;
}

FGameplayTag UACFFunctionLibrary::GetWeaponTypeTagRoot()
{
	UACFDeveloperSettings* settings = GetMutableDefault< UACFDeveloperSettings>();

	if (settings)
	{
		return settings->WeaponTypeTag;
	}
	UE_LOG(LogTemp, Warning, TEXT("Missing Tag! - UACFFunctionLibrary "));

	return FGameplayTag();
}

FGameplayTag UACFFunctionLibrary::GetWeaponSlotTagRoot()
{
	UACFDeveloperSettings* settings = GetMutableDefault< UACFDeveloperSettings>();

	if (settings)
	{
		return settings->WeaponSlotsTag;
	}
	UE_LOG(LogTemp, Warning, TEXT("Missing Tag! - UACFFunctionLibrary "));

	return FGameplayTag();
}


FGameplayTag UACFFunctionLibrary::GetMovesetTypeTagRoot()
{
	UACFDeveloperSettings* settings = GetMutableDefault< UACFDeveloperSettings>();

	if (settings)
	{
		return settings->MovesetTypeTag;
	}
	UE_LOG(LogTemp, Warning, TEXT("Missing Moveset Root Tag! - UACFFunctionLibrary "));

	return FGameplayTag();
}

FGameplayTag UACFFunctionLibrary::GetAnimationOverlayTagRoot()
{
	UACFDeveloperSettings* settings = GetMutableDefault< UACFDeveloperSettings>();

	if (settings)
	{
		return settings->AnimationOverlayTag;
	}
	UE_LOG(LogTemp, Warning, TEXT("Missing Animation Overlay Root Tag! - UACFFunctionLibrary "));

	return FGameplayTag();
}

bool UACFFunctionLibrary::IsValidWeaponTypeTag(FGameplayTag TagToCheck)
{
	FGameplayTag root = GetWeaponTypeTagRoot();

	return UGameplayTagsManager::Get().RequestGameplayTagChildren(root).HasTag(TagToCheck);
}

bool UACFFunctionLibrary::IsValidItemSlotTag(FGameplayTag TagToCheck)
{
	FGameplayTag root = GetWeaponSlotTagRoot();

	return UGameplayTagsManager::Get().RequestGameplayTagChildren(root).HasTag(TagToCheck);
}

// bool UACFFunctionLibrary::IsValidArmorSlotTag(FGameplayTag TagToCheck)
// {
// 	FGameplayTag root = GetArmorSlotTagRoot(WorldContextObject);
// 
// 	return UGameplayTagsManager::Get().RequestGameplayTagChildren(root).HasTag(TagToCheck);
// }

bool UACFFunctionLibrary::IsValidMovesetTypeTag(FGameplayTag TagToCheck)
{
	FGameplayTag root = GetMovesetTypeTagRoot();

	return UGameplayTagsManager::Get().RequestGameplayTagChildren(root).HasTag(TagToCheck);
}

bool UACFFunctionLibrary::IsValidAnimOverlayTag(FGameplayTag TagToCheck)
{
	FGameplayTag root = GetAnimationOverlayTagRoot();

	return UGameplayTagsManager::Get().RequestGameplayTagChildren(root).HasTag(TagToCheck);
}

void UACFFunctionLibrary::PlayImpactEffect(const FImpactEffect& effect, const FVector& impactLocation, class AActor* instigator, const UObject* WorldContextObject)
{

	if (effect.CameraShake && effect.bShouldShakeCamera && WorldContextObject) {
		UGameplayStatics::PlayWorldCameraShake(WorldContextObject, effect.CameraShake, impactLocation, 0.f, effect.ShakeRadius, effect.ShakeFalloff);
	}

	if (effect.bShouldMakeDamage && instigator) {
		UACMCollisionManagerComponent *collComp = instigator->FindComponentByClass<UACMCollisionManagerComponent>();

		if (!collComp) {
			return;
		}

		collComp->StartTimedSingleTrace(effect.DamageTraceName, effect.DamageTraceDuration);
	}
}

void UACFFunctionLibrary::PlayActionEffect(const FEffect& effect, AACFCharacter* instigator, const UObject* WorldContextObject)
{
	AACFGameState* gameState = UACFFunctionLibrary::GetACFGameState(WorldContextObject);

	if (gameState) {
		UACFEffectsDispatcherComponent* EffectComp = gameState->GetEffectsComponent();
		EffectComp->ServerPlayReplicatedEffect(effect, instigator);
		return;
	}

	UE_LOG(LogTemp, Warning, TEXT("Missing ACFGameState! - UACFFunctionLibrary "));
}

void UACFFunctionLibrary::PlayActionEffectLocally(const FEffect& effect, class AACFCharacter* instigator, const UObject* WorldContextObject)
{
	AACFGameState* gameState = UACFFunctionLibrary::GetACFGameState(WorldContextObject);

	if (gameState) {
		UACFEffectsDispatcherComponent* EffectComp = gameState->GetEffectsComponent();
		EffectComp->PlayEffectLocally(effect, instigator);
		return;
	}

	UE_LOG(LogTemp, Warning, TEXT("Missing ACFGameState! - UACFFunctionLibrary "));
}

EBattleType UACFFunctionLibrary::GetBattleType(const UObject* WorldContextObject)
{
	AACFGameState* gameState = Cast<AACFGameState>(UGameplayStatics::GetGameState(WorldContextObject));

	if (gameState)
	{
		return gameState->GetBattleType();
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Trying to get battle type from client! COnfigurations must be done on server!! - UACFFunctionLibrary "));

	}
	return EBattleType::ETeamBased;
}

TSubclassOf<AACFWorldItem>  UACFFunctionLibrary::GetDefaultWorldItemClass()
{
	UACFDeveloperSettings* settings = GetMutableDefault< UACFDeveloperSettings>();

	if (settings)
	{
		return settings->WorldItemClass;
	
	}
	UE_LOG(LogTemp, Warning, TEXT("Missing Default Item Class! - UACFFunctionLibrary "));

	return nullptr;
}

TSubclassOf<UACFDamageCalculation> UACFFunctionLibrary::GetDamageCalculationClass()
{
	UACFDeveloperSettings* settings = GetMutableDefault< UACFDeveloperSettings>();

	if (settings)
	{
		return settings->DamageCalculatorClass;

	}
	UE_LOG(LogTemp, Warning, TEXT("Missing DamageCalculator Class! - UACFFunctionLibrary "));

	return nullptr;
}

bool UACFFunctionLibrary::AreEnemyTeams(ETeam teamA, ETeam teamB)
{
	if (teamA == ETeam::ENeutral || teamB == ETeam::ENeutral)
		return false;

	return teamA != teamB;
}



float UACFFunctionLibrary::CalculateDistanceBetweenCharactersExtents(const ACharacter* characterA, const ACharacter* characterB)
{

	if (characterA && characterB) {
		FVector extentA, extentB, originA, originB;
		FBox aBox = characterA->GetMesh()->Bounds.GetBox();
		FBox bBox = characterB->GetMesh()->Bounds.GetBox();

		const float dist = characterA->GetDistanceTo(characterB);
		return dist - aBox.GetExtent().X - bBox.GetExtent().X;
	}
	return -1.f;

}



float UACFFunctionLibrary::CalculateAngleBetweenVectors(const FVector& vectorA, const FVector& vectorB)
{
	return FMath::RadiansToDegrees(acosf(FVector::DotProduct(vectorA, vectorB)));
}

class AACFHUD* UACFFunctionLibrary::GetACFHUD(const UObject* WorldContextObject)
{
	APlayerController * playerController = UGameplayStatics::GetPlayerController(WorldContextObject, 0);

	return Cast<AACFHUD> (playerController->GetHUD());
}

class AACFPlayerController* UACFFunctionLibrary::GetLocalACFPlayerController(const UObject* WorldContextObject)
{
	return Cast< AACFPlayerController>(UGameplayStatics::GetPlayerController(WorldContextObject,0));
}

class AACFGameMode* UACFFunctionLibrary::GetACFGameMode(const UObject* WorldContextObject)
{
	return Cast< AACFGameMode>(UGameplayStatics::GetGameMode(WorldContextObject));
}

class AACFGameState* UACFFunctionLibrary::GetACFGameState(const UObject* WorldContextObject)
{
	return Cast< AACFGameState>(UGameplayStatics::GetGameState(WorldContextObject));
}

class AACFCharacter* UACFFunctionLibrary::GetLocalACFPlayerCharacter(const UObject* WorldContextObject)
{
	return Cast< AACFCharacter>(UGameplayStatics::GetPlayerCharacter(WorldContextObject, 0));
}

void UACFFunctionLibrary::SpawnWorldItemNearLocation( UObject* WorldContextObject, TArray<FBaseItem> ContainedItems, FVector location, float acceptanceRadius /*= 100.f*/)
{
	FVector outLoc;
	if (UNavigationSystemV1::K2_GetRandomLocationInNavigableRadius(WorldContextObject, location, outLoc, acceptanceRadius))
	{
		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

		TSubclassOf<AACFWorldItem> WorldItemClass = UACFFunctionLibrary::GetDefaultWorldItemClass();
		ensure(WorldItemClass);

		APlayerController* playerController = UGameplayStatics::GetPlayerController(WorldContextObject, 0);
		UWorld* world = playerController->GetWorld();

		if (!world)
			return ;

		if (world && WorldItemClass)
		{
			AACFWorldItem* _worldItem = world->SpawnActor<AACFWorldItem>(WorldItemClass, outLoc, FRotator(0), SpawnParams);
			if (_worldItem)
			{
				_worldItem->SetItemsArray(ContainedItems);
			}
		}
		else
		{
			UE_LOG(LogTemp, Log, TEXT("Impossible to Spawn Item!! - ACFEquipmentComp"));
		}
	}
}
