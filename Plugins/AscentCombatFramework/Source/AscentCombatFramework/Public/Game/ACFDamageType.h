// Copyright (C) Pakyman Prod. 2020. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/DamageType.h"
#include <GameplayTagContainer.h>
#include "ACFData.h"
#include <Engine/EngineTypes.h>
#include "ACFDamageType.generated.h"

/**
 * 
 */


UCLASS()
class ASCENTCOMBATFRAMEWORK_API UACFDamageType : public UDamageType
{
	GENERATED_BODY()


public:

	UACFDamageType();
 
};

UCLASS()
class ASCENTCOMBATFRAMEWORK_API UMeleeDamageType : public UACFDamageType
{
	GENERATED_BODY()

};

UCLASS()
class ASCENTCOMBATFRAMEWORK_API URangedDamageType : public UACFDamageType
{
	GENERATED_BODY()

};

UCLASS()
class ASCENTCOMBATFRAMEWORK_API UAreaDamageType : public UACFDamageType
{
	GENERATED_BODY()

};

UCLASS()
class ASCENTCOMBATFRAMEWORK_API USpellDamageType : public UACFDamageType
{
	GENERATED_BODY()

};

UCLASS()
class ASCENTCOMBATFRAMEWORK_API UFallDamageType : public UACFDamageType
{
	GENERATED_BODY()

};

USTRUCT(BlueprintType)
struct FACFDamageEvent 
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadWrite, Category = ACF)
	FName contextString;

	UPROPERTY(BlueprintReadWrite, Category = ACF)
	float DamageMultiplier;

	UPROPERTY(BlueprintReadWrite, Category = ACF)
	class AACFCharacter* DamageDealer;

	UPROPERTY(BlueprintReadWrite, Category = ACF)
	class AActor* DamageReceiver;

	UPROPERTY(BlueprintReadWrite, Category = ACF)
	class UPhysicalMaterial* PhysMaterial;

	UPROPERTY(BlueprintReadWrite, Category = ACF)
	EDamageZone DamageZone;

	UPROPERTY(BlueprintReadWrite, Category = ACF)
	float FinalDamage;

	UPROPERTY(BlueprintReadWrite, Category = ACF)
	FHitResult hitResult;

	UPROPERTY(BlueprintReadWrite, Category = ACF)
	FVector hitDirection;

	UPROPERTY(BlueprintReadWrite, Category = ACF)
	FGameplayTag HitResponseAction;

	UPROPERTY(BlueprintReadWrite, Category = ACF)
	TSubclassOf<class UDamageType> DamageClass;

	UPROPERTY(BlueprintReadWrite, Category = ACF)
	EDirection DamageDirection;

};
