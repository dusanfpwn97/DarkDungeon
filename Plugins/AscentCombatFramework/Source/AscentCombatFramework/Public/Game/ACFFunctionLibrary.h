// Copyright (C) Pakyman Prod. 2020. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include <GameplayTagContainer.h>
#include <Engine/DataTable.h>
#include "ARSStatisticsData.h"
#include "ACFData.h"
#include "Items/ACFItem.h"
#include "ACFDamageType.h"
#include "ACFFunctionLibrary.generated.h"


UCLASS()
class ASCENTCOMBATFRAMEWORK_API UACFFunctionLibrary   : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
	
public:

	UFUNCTION(BlueprintCallable, Category = ACFLibrary)
	static EDirection GetHitDirectionByHitResult(const AActor* hitDealer, const FHitResult& hitResult);

	UFUNCTION(BlueprintCallable, Category = ACFLibrary)
	static FVector GetActorsRelativeDirectionVector(const FACFDamageEvent& damageEvent);

	UFUNCTION(BlueprintCallable, Category = ACFLibrary)
	static bool DoesDamageInvolveLocalPlayer(const FACFDamageEvent& damageEvent);

	UFUNCTION(BlueprintCallable, Category = ACFLibrary)
	static EDirection GetActorsRelativeDirection(const AActor* hitDealer, const AActor* receiver);

	UFUNCTION(BlueprintCallable, Category = ACFLibrary)
	static FVector GetActorsOppositeRelativeDirection(const FACFDamageEvent& damageEvent);

	UFUNCTION(BlueprintCallable, Category = ACFLibrary)
	static FGameplayTag GetDefaultActionsState();

	UFUNCTION(BlueprintCallable, Category = ACFLibrary)
	static FGameplayTag GetDefaultDeathState();

	UFUNCTION(BlueprintCallable, Category = ACFLibrary)
	static FGameplayTag GetDefaultHitState();

	UFUNCTION(BlueprintCallable, Category = ACFLibrary)
	static FGameplayTag GetHealthTag();

	UFUNCTION(BlueprintCallable, Category = ACFLibrary)
	static float ApplyRandomDeviationToDamage(float Damage);

	UFUNCTION(BlueprintCallable, Category = ACFLibrary)
	static float ReduceDamageByPercentage(float Damage, float Percentage);

	UFUNCTION(BlueprintCallable, Category = ACFLibrary)
	static float GetDamageMultiplierByDamageZone(EDamageZone DamagedZone);

	UFUNCTION(BlueprintCallable, Category = ACFLibrary)
	static FGameplayTag GetWeaponTypeTagRoot();

	UFUNCTION(BlueprintCallable, Category = ACFLibrary)
	static FGameplayTag GetWeaponSlotTagRoot();

	// 	UFUNCTION(BlueprintCallable)
	// 	static FGameplayTag GetArmorSlotTagRoot();

	UFUNCTION(BlueprintCallable, Category = ACFLibrary)
	static 	FGameplayTag GetMovesetTypeTagRoot();

	UFUNCTION(BlueprintCallable, Category = ACFLibrary)
	static 	FGameplayTag GetAnimationOverlayTagRoot();

	UFUNCTION(BlueprintCallable, Category = ACFLibrary)
	static 	bool IsValidWeaponTypeTag(FGameplayTag TagToCheck);

	UFUNCTION(BlueprintCallable, Category = ACFLibrary)
	static  bool IsValidItemSlotTag(FGameplayTag TagToCheck);

	// 	UFUNCTION(BlueprintCallable)
	// 	static  bool IsValidArmorSlotTag(FGameplayTag TagToCheck);

	UFUNCTION(BlueprintCallable, Category = ACFLibrary)
	static  bool IsValidMovesetTypeTag(FGameplayTag TagToCheck);

	UFUNCTION(BlueprintCallable, Category = ACFLibrary)
	static  bool IsValidAnimOverlayTag(FGameplayTag TagToCheck);
 
	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject"), Category = ACFLibrary)
	static void PlayImpactEffect(const FImpactEffect& effect, const FVector& impactLocation, class AActor* instigator, const UObject* WorldContextObject);

	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject"), Category = ACFLibrary)
	static void PlayActionEffect(const FEffect& effect, class AACFCharacter* instigator, const UObject* WorldContextObject);

	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject"), Category = ACFLibrary)
	static void PlayActionEffectLocally(const FEffect& effect, class AACFCharacter* instigator, const UObject* WorldContextObject);

	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject"), Category = ACFLibrary)
	static EBattleType GetBattleType(const UObject* WorldContextObject);

	UFUNCTION(BlueprintPure, Category = ACFLibrary)
	static TSubclassOf<class AACFWorldItem> GetDefaultWorldItemClass();

	UFUNCTION(BlueprintPure, Category = ACFLibrary)
    static TSubclassOf<class UACFDamageCalculation> GetDamageCalculationClass();

	UFUNCTION(BlueprintCallable, Category = ACFLibrary)
	static bool AreEnemyTeams(ETeam teamA, ETeam teamB);

	UFUNCTION(BlueprintCallable, Category = ACFLibrary)
	static float CalculateDistanceBetweenCharactersExtents(const ACharacter* characterA, const ACharacter* characterB);
	
	UFUNCTION(BlueprintCallable, Category = ACFLibrary)
	static float CalculateAngleBetweenVectors(const FVector& vectorA, const FVector& vectorB);

	UFUNCTION(BlueprintPure, meta = (WorldContext = "WorldContextObject"), Category = ACFLibrary)
	static class AACFHUD* GetACFHUD(const UObject* WorldContextObject);


	UFUNCTION(BlueprintPure, meta = (WorldContext = "WorldContextObject"), Category = ACFLibrary)
	static class AACFPlayerController* GetLocalACFPlayerController(const UObject* WorldContextObject);

	/*Works on server only*/
	UFUNCTION(BlueprintPure, meta = (WorldContext = "WorldContextObject"), Category = ACFLibrary)
	static class AACFGameMode* GetACFGameMode(const UObject* WorldContextObject);

	UFUNCTION(BlueprintPure, meta = (WorldContext = "WorldContextObject"), Category = ACFLibrary)
	static class AACFGameState* GetACFGameState(const UObject* WorldContextObject);

	UFUNCTION(BlueprintPure, meta = (WorldContext = "WorldContextObject"), Category = ACFLibrary)
	static class AACFCharacter* GetLocalACFPlayerCharacter(const UObject* WorldContextObject);

	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject"), Category = ACFLibrary)
	static void SpawnWorldItemNearLocation( UObject* WorldContextObject, TArray<FBaseItem> ContainedItems, FVector location, float acceptanceRadius = 100.f);


	template<typename TEnum> static FORCEINLINE FString GetEnumValueAsString(const FString& Name, TEnum Value)
	{

		const UEnum* enumPtr = FindObject<UEnum>(ANY_PACKAGE, *Name, true);
		if (!enumPtr)
		{
			return FString("Invalid");
		}

		return enumPtr->GetNameByValue((int64)Value).ToString();
	}
};
