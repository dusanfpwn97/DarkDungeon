// Copyright (C) Pakyman Prod. 2020. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include <Engine/DataTable.h>
#include "ARSStatisticsData.h"
#include <GameFramework/DamageType.h>
#include "Templates/SubclassOf.h"
#include "ACFData.generated.h"

/**
 *
 */
class AACFCharacter;

UENUM(BlueprintType)
enum class ELocomotionState : uint8
{
	EIdle = 0       UMETA(DisplayName = "Idle"),
	EWalk			UMETA(DisplayName = "Walk"),
	EJog			UMETA(DisplayName = "Jog"),
	ESprint			UMETA(DisplayName = "Sprint"),
};

UENUM(BlueprintType)
enum class EDeathType : uint8
{
	EGoRagdoll = 0       UMETA(DisplayName = "Go Ragdoll"),
	EDeathAction         UMETA(DisplayName = "Trigger Death Action"),
	EDestroyImmediately  UMETA(DisplayName = "Destroy Actor Immediately"),
	EDoNothing           UMETA(DisplayName = "Do Nothinh"),
};


USTRUCT(BlueprintType)
struct FActionState : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = ACF)
		class UAnimMontage* MontageAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Instanced, Category = ACF)
		class UACFBaseAction* Action;

};

USTRUCT(BlueprintType)
struct FRagdollImpulse 
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = ACF)
	float ImpulseIntensity = 800.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = ACF)
	FVector ImpulseDirection;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = ACF)
	FName BoneName;

	FRagdollImpulse(){};

};


UENUM(BlueprintType)
enum class EDamageActivationType : uint8
{
	ERight        UMETA(DisplayName = "Right Weapon Only"),
	ELeft		  UMETA(DisplayName = "Left Weapon Only"),
	EBoth		  UMETA(DisplayName = "Left And Right Weapon"),
	EPhysical      UMETA(DisplayName = "Physical Damage"),
};

UENUM(BlueprintType)
enum class EBattleState : uint8
{
	EExploration        UMETA(DisplayName = "Exploration"),
	EBattle		 UMETA(DisplayName = "Battle"),
};

UENUM(BlueprintType)
enum class EDamageZone : uint8
{
	ENormal         UMETA(DisplayName = "Normal Zone"),
	EImmune		 UMETA(DisplayName = "Zero Damage Zone"),
	EHighDefense	 UMETA(DisplayName = "High Defense Zone"),
	EHighDamage	 UMETA(DisplayName = "High Damage Zone"),
};

UENUM(BlueprintType)
enum class EDirection : uint8
{
	Front  = 0,
	Back = 1,
	Left = 2,
	Right = 3
};

UENUM(BlueprintType)
enum class EActionDirection : uint8
{
	Front  = 0			UMETA(DisplayName = "Front Only"),
	Back  = 1			UMETA(DisplayName = "Back Only"), 
	Left = 2			UMETA(DisplayName = "Left Only"),
	Right  = 3			 UMETA(DisplayName = "Right Only"),
	EveryDirection = 4 UMETA(DisplayName = "Every Direction"),
};

UENUM(BlueprintType)
enum class EBattleType : uint8
{
	ETeamBased   UMETA(DisplayName = "Heroes Against Enemies"),
	EEveryonAgainstEveryone	 UMETA(DisplayName = "Everyone Against Everyone"),
};


UENUM(BlueprintType)
enum class EMontageReproductionType : uint8
{
	ERootMotion							UMETA(DisplayName = "Root Motion"),
	ECurveOverrideSpeed 				UMETA(DisplayName = "Override Speed with Curve"),
	ECurveSnapsOnTarget 				UMETA(DisplayName = "Override Speed and Snaps To Target"),
	ECurveOverrideSpeedAndDirection 	UMETA(DisplayName = "Override Speed and Direction Vector"),
};

UENUM(BlueprintType)
enum class EAIState : uint8
{
	EPatrol = 0			UMETA(DisplayName = "Patrol"),
	EBattle = 1 	    UMETA(DisplayName = "Combat"),
	EFollowLeader = 2	UMETA(DisplayName = "Go Home"),     
	EWait = 3           UMETA(DisplayName = "Wait"),
};

UENUM(BlueprintType)
enum class EAICombatState : uint8
{
	EMeleeCombat = 0         UMETA(DisplayName = "Melee Attacks"),
	EMeleePostAttack = 1     UMETA(DisplayName = "Melee Post Attacks"),	
	ERangedCombat = 2		 UMETA(DisplayName = "Ranged Attacks"),
	EStudyTarget = 3         UMETA(DisplayName = "Studytarget"),
	EFlee = 4                UMETA(DisplayName = "Flee Away"),
};


UENUM(BlueprintType)
enum class EActionPriority : uint8
{
	ENone   UMETA(DisplayName = "Very Low"),
	ELow    UMETA(DisplayName = "Low"),
	EMedium UMETA(DisplayName = "Medium"),
	EHigh   UMETA(DisplayName = "High"),
	EHighest  UMETA(DisplayName = "Highest"),
};

UENUM(BlueprintType)
enum class ESpawnFXLocation : uint8
{
	ESpawnOnActorLocation  UMETA(DisplayName = "Actor Location"),
	ESpawnAttachedToSocketOrBone UMETA(DisplayName = "Socket Or BoneLocation"),
	ELastDamageLocation    UMETA(DisplayName = "Last Damage Impact Location")
};

UENUM(BlueprintType)
enum class EConditionType : uint8
{
	EBelow UMETA(DisplayName = "Is Below"),
	EEqual UMETA(DisplayName = "Is Nearly Equal"),
	EAbove UMETA(DisplayName = "Is Above"),
};

UENUM(BlueprintType)
enum class EAbilityType : uint8
{
	EActive  UMETA(DisplayName = "Active: Activate Once and Destroy"),
	EPassive  UMETA(DisplayName = "Passive: Stay Activated"),
};

USTRUCT(BlueprintType)
struct FAISpawnInfo
{
	GENERATED_BODY()


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = ACF)
	TSubclassOf<class AACFCharacter> AIClassBP;

	UPROPERTY(EditAnywhere, BlueprintReadOnly,  Category = ACF)
	/** the number of this ai class in group*/
	int32 TotalNumber = 1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = ACF)
	/** the max number of Col this ai class has in group*/
	int32 MaxNumOfCol = 5;

	UPROPERTY()
	int32 NumOfRow;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = ACF)
	/** the distance between each ai in same row */
	float ColumnPadding = 250;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = ACF)
	/** the distance between each ai in same column */
	float RowPadding = 250;
};

USTRUCT(BlueprintType)
struct FAIAgentsInfo
{
	GENERATED_BODY()

public:

	FAIAgentsInfo() {};

	FAIAgentsInfo(class AACFCharacter* inChar,  class AACFAIController* inContr)
	{
		AICharacter = inChar;
		AIController = inContr;
	}

	FORCEINLINE	bool operator==(const FAIAgentsInfo &Other) const
	{
		return this->AICharacter == Other.AICharacter;
	}

	FORCEINLINE	bool operator!=(const FAIAgentsInfo &Other) const
	{
		return this->AICharacter != Other.AICharacter;
	}

	FORCEINLINE	bool operator==(const AACFCharacter* Other) const
	{
		return this->AICharacter == Other;
	}

	FORCEINLINE	bool operator!=(const AACFCharacter* Other) const
	{
		return this->AICharacter != Other;
	}


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, SaveGame, Category = ACF)
	class AACFCharacter* AICharacter;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, SaveGame, Category = ACF)
	class AACFAIController* AIController;

};

USTRUCT(BlueprintType)
struct FSnapConfiguration
{
	GENERATED_BODY()

public:

	UPROPERTY( BlueprintReadWrite, Category = ACF)
	AActor* target;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ACF)
	float preferredDistance = 150.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ACF)
	float maxSnapMultiplier = 2.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ACF)
	float RotationRateSnapMult = 1.0f;

};

USTRUCT(BlueprintType)
struct FEffect : public FTableRowBase
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ACF)
		ESpawnFXLocation SpawnLocation = ESpawnFXLocation::ESpawnOnActorLocation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ACF)
		class USoundCue* ActionSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ACF)
		FName SocktOrBoneName = NAME_None;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ACF)
		class UParticleSystem* ActionParticle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ACF)
		float NoiseEmitted = 0.f;

};

USTRUCT(BlueprintType)
struct FImpactEffect
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ACF)
	bool bShouldShakeCamera;

	UPROPERTY(EditAnywhere, meta = (EditCondition = bShouldShakeCamera), BlueprintReadWrite, Category = ACF)
	TSubclassOf<class UCameraShake> CameraShake;

	UPROPERTY(EditAnywhere, meta = (EditCondition = bShouldShakeCamera), BlueprintReadWrite, Category = ACF)
	float ShakeFalloff = 100.f;

	UPROPERTY(EditAnywhere, meta = (EditCondition = bShouldShakeCamera), BlueprintReadWrite, Category = ACF)
	float ShakeRadius = 1.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ACF)
	bool bShouldMakeDamage;

	UPROPERTY(EditAnywhere, meta = (EditCondition = bShouldMakeDamage), BlueprintReadWrite, Category = ACF)
	FName DamageTraceName;

	UPROPERTY(EditAnywhere, meta = (EditCondition = bShouldMakeDamage), BlueprintReadWrite, Category = ACF)
	float DamageTraceDuration;

};



USTRUCT(BlueprintType)
struct FActionConfig
{
	GENERATED_BODY()

public:


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ACFStatConfig)
	TArray<FStatisticModifier> ActionCost;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ACFStatConfig)
	TArray<FAttribute> Requirements;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ACFStatConfig)
	FAttributesSetModifier AttributeModifier;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ACFActionConfig)
	FEffect ActionEffects;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ACFActionConfig)
	bool bPerformableInAir = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ACFActionConfig)
	bool bCanBeStored = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ACFActionConfig)
	float CoolDownTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ACFAnimConfig)
	bool bPlayRandomMontageSection = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ACFAnimConfig)
	bool bBindActionToAnimation = true;

	/*Decide if we have to stop AIController's BT during this action*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ACFAnimConfig)
	bool bStopBehavioralThree = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ACFAnimConfig)
	bool bPlayEffectOnActionStart = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ACFAnimConfig)
	EMontageReproductionType MontageReproductionType = EMontageReproductionType::ERootMotion;

};

USTRUCT(BlueprintType)
struct FCommandChances : public FTableRowBase
{
	GENERATED_BODY()

public:


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = ACF)
	FGameplayTag CommandTag;

	UPROPERTY(EditAnywhere, Instanced, BlueprintReadOnly, Category = ACF)
	class UACFActionCondition* Conditions;

};

USTRUCT(BlueprintType)
struct FAICombatStateConfig 
{
	GENERATED_BODY()

public:


	FAICombatStateConfig() {};

	FAICombatStateConfig(float inDistance, float inChance, ELocomotionState inState) {
		IdealDistance = inDistance;
		TriggerChancePercentage = inChance;
		LocomotionState = inState;
	}
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ACF)
	float IdealDistance = 100.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ACF)
	float TriggerChancePercentage = 75.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ACF)
	 ELocomotionState LocomotionState = ELocomotionState::EWalk;

};


USTRUCT(BlueprintType)
struct FActionChances : public FTableRowBase
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = ACF)
	EActionDirection AllowedFromDirection;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = ACF)
	FGameplayTag ActionTag;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = ACF)
	float ChancePercentage = 100.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = ACF)
	float BTWaitTime = 0.5f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = ACF)
	EActionPriority Priority = EActionPriority::ELow ;

};


USTRUCT(BlueprintType)
struct FActionsChances
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = ACF)
	TArray< FActionChances> PossibleActions;

};



USTRUCT(BlueprintType)
struct FOnHitActionChances : public FActionChances
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = ACF)
	TArray<TSubclassOf<UDamageType>> AllowedDamageTypes;

};



USTRUCT(BlueprintType)
struct FConditions : public FActionChances
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Instanced, Category = ACF)
	class UACFActionCondition* Condition;

};

USTRUCT(BlueprintType)
struct FEffectByDamageType : public FTableRowBase
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = ACF)
	TMap<TSubclassOf<UDamageType>, FEffect> EffectByDamageType;

};


UENUM(BlueprintType)
enum class ETeam : uint8
{
	EEnemiesTeam   UMETA(DisplayName = "Enemies Team"),
	EHeroesTeam	 UMETA(DisplayName = "Heroes Team"),
	ENeutral     UMETA(DisplayName= "Neutral")
};

UENUM(BlueprintType)
enum class ECombatType : uint8
{
	EUnarmed   UMETA(DisplayName = "Unarmed"),
	EMelee	    UMETA(DisplayName = "Melee"),
	ERanged    UMETA(DisplayName = "Ranged"),
};

UENUM(BlueprintType)
enum class ECombatBehaviorType : uint8
  {
	EMelee	    UMETA(DisplayName = "Melee"),
	ERanged     UMETA(DisplayName = "Ranged"),
};


UCLASS()
class ASCENTCOMBATFRAMEWORK_API UACFData : public UObject
{
	GENERATED_BODY()
	
};
