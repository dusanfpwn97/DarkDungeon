// Copyright (C) Pakyman Prod. 2020. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include <GameFramework/DamageType.h>
#include "ACMTypes.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct FHitActors
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = ACM)
	TArray<class AActor*> AlreadyHitActors;

};



UENUM(BlueprintType)
enum class EDebugType : uint8
{
	EDontShowDebugInfos  UMETA(DisplayName = "Don't Show Debug Info"),
	EShowInfoDuringSwing UMETA(DisplayName = "Show Info During Swing"),
	EAlwaysShowDebug	 UMETA(DisplayName = "Always Show Debug Info"),
};


UENUM(BlueprintType)
enum class EDamageType : uint8
{
	EPoint  UMETA(DisplayName = "Point Damage"),
	EArea   UMETA(DisplayName = "Area Damage"),
};

USTRUCT(BlueprintType)
struct FTraceInfo
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = ACM)
	FName StartSocket;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = ACM)
	FName EndSocket;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = ACM)
	float Radius;

	/** Select if it's Area or Point Damage*/
	UPROPERTY(BlueprintReadOnly, EditAnywhere, meta = (EditCondition = bAutoApplyDamage), Category = ACM)
	EDamageType DamageType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ACM)
	class USoundCue* AttackSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ACM)
	class UParticleSystem* AttackParticle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ACM)
	float TrailLength = 1.f;

	/** The type of damage applied*/
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (EditCondition = bAutoApplyDamage), Category = ACM)
	TSubclassOf<UDamageType> DamageTypeClass = UDamageType::StaticClass();

	/** The base damage to apply to the actor (Can be modified in you TakeDamage Implementation)*/
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (EditCondition = bAutoApplyDamage), Category = ACM)
	float BaseDamage = 0.f;

};


UCLASS()
class COLLISIONSMANAGER_API UACMTypes : public UObject
{
	GENERATED_BODY()
	
};
