// Copyright (C) Pakyman Prod. 2020. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include <Engine/DataTable.h>
#include <Curves/CurveFloat.h>
#include <GameplayTagContainer.h>
#include "ARSStatisticsData.generated.h"

/**
 * 
 */


UENUM(BlueprintType)
enum class EModifierType : uint8
{
	EAdditive = 0       UMETA(DisplayName = "Additive"),
	EPercentage         UMETA(DisplayName = "Percentage"),
};


UENUM(BlueprintType)
enum class EStatsLoadMethod : uint8
{
	EUseDefaultsWithoutGeneration = 0       UMETA(DisplayName = "Use Defaults Without Generation"),
	EGenerateFromDefaultsPrimary            UMETA(DisplayName = "Generate From Default Attributes"),
	ELoadByLevel							UMETA(DisplayName = "Load By Actual Level From Curves")
};

UENUM(BlueprintType)
enum class ELevelingType : uint8
{
	ECantLevelUp = 0             UMETA(DisplayName = "Do not use Leveling System"),
	EGenerateNewStatsFromCurves  UMETA(DisplayName = "Generate Stats From Curves"),
	EAssignPerksManually		UMETA(DisplayName = "Assign Perks Manually"),
};

UENUM(BlueprintType)
enum class EStatisticsType : uint8
{
	EStatistic = 0       UMETA(DisplayName = "Statistic"),
	EPrimaryAttribute         UMETA(DisplayName = "Attributes"),
	ESecondaryAttribute         UMETA(DisplayName = "Parameters"),
};


USTRUCT(BlueprintType)
struct FStatistic : public FTableRowBase
{
	GENERATED_BODY()

public:

	//default constructor
	FStatistic()
	{
		MaxValue = CurrentValue = 100.f;
		RegenValue =  0.f;
	}
	FStatistic(FGameplayTag _statType, float _maxValue, float _regenValue, float _regenDelay = 0.f)
	{
		StatType = _statType;
		MaxValue = CurrentValue = _maxValue;
		RegenValue = _regenValue;
		RegenDelay = _regenDelay;
	}
	~FStatistic() {};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = StatData)
	FGameplayTag StatType;

	//maximum stat value
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = StatData)
	float MaxValue;

	//current stat value
	UPROPERTY(BlueprintReadOnly, Category = StatData, meta = (ClampMin = 0))
	float CurrentValue;

	/*Indicates if this stat can regenerate over time*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = StatData)
		bool HasRegeneration;

	//value added to stat with every timer tick if HasRegeneration is enabled
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = StatData)
	float RegenValue;

	//time you have to wait after the statistic is modified to let regeneration start
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = StatData)
	float RegenDelay;

	FORCEINLINE	bool	operator==(const FStatistic &Other) const
	{
		return this->StatType == Other.StatType;
	}

	FORCEINLINE	bool	operator!=(const FStatistic &Other) const
	{
		return this->StatType != Other.StatType;
	}

	FORCEINLINE	FStatistic	operator+(const FStatistic &Other) const
	{
		FStatistic _att = *(this);
		float _oldmaxvalue = _att.MaxValue;
		if (Other.StatType == this->StatType)
		{
			_att.MaxValue += Other.MaxValue;
			_att.RegenValue += Other.RegenValue;
			_att.HasRegeneration = _att.RegenValue != 0.f;
			_att.RegenDelay  += Other.RegenDelay;
		//	_att.CurrentValue = UARSFunctionLibrary::GetNewCurrentValueForNewMaxValue(CurrentValue, _oldmaxvalue, _att.MaxValue);
		}
		return _att;
	}

	FORCEINLINE	FStatistic	operator-(const FStatistic &Other) const
	{
		FStatistic _att = *(this);
		float _oldmaxvalue = _att.MaxValue;
		if (Other.StatType == this->StatType)
		{
			_att.MaxValue -= Other.MaxValue;
			_att.RegenValue -= Other.RegenValue;
			_att.HasRegeneration = _att.RegenValue != 0.f;
			_att.RegenDelay -= Other.RegenDelay;
		//	_att.CurrentValue = UARSFunctionLibrary::GetNewCurrentValueForNewMaxValue(CurrentValue, _oldmaxvalue, _att.MaxValue);

		}
		return _att;
	}

	FORCEINLINE	bool operator==(const FGameplayTag Other) const
	{
		return this->StatType == Other;
	}

	FORCEINLINE	bool operator!=(const FGameplayTag Other) const
	{
		return this->StatType != Other;
	}
};

USTRUCT(BlueprintType)
struct FAttribute : public FTableRowBase
{
	GENERATED_BODY()

		//default constructor
		FAttribute()
	{
		Value = 0.f;

	}

	FAttribute(FGameplayTag _stat, float _value)
	{
		Value = _value;
		AttributeType = _stat;
	}

	~FAttribute() {};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = StatData)
		FGameplayTag AttributeType;

	//current stat value
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = StatData)
		float Value;

	FORCEINLINE	FAttribute	operator+(const FAttribute &Other) const
	{
		FAttribute _att;
		_att.AttributeType = this->AttributeType;
		_att.Value = this->Value;
		if (Other.AttributeType == this->AttributeType)
		{
			_att.Value += Other.Value;
		}
		return _att;
	}

	FORCEINLINE	FAttribute	operator-(const FAttribute &Other) const
	{
		FAttribute _att;
		_att.AttributeType = this->AttributeType;
		_att.Value = this->Value;
		if (Other.AttributeType == this->AttributeType)
		{
			_att.Value -= Other.Value;
		}
		return _att;
	}

	FORCEINLINE	bool operator==(const FAttribute &Other) const
	{
		return this->AttributeType == Other.AttributeType;
	}

	FORCEINLINE	bool operator==(const FGameplayTag& Other) const
	{
		return this->AttributeType == Other;
	}
	FORCEINLINE	bool operator!=(const FGameplayTag& Other) const
	{
		return this->AttributeType != Other;
	}
	FORCEINLINE	bool operator!=(const FAttribute &Other) const
	{
		return this->AttributeType != Other.AttributeType;
	}

};

USTRUCT(BlueprintType)
struct FAttributesSet : public FTableRowBase
{
	GENERATED_BODY()

public:

	//default constructor
	FAttributesSet() {}


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ARS)
	TArray<FStatistic> Statistics;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ARS)
	TArray<FAttribute> Parameters;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ARS)
	TArray<FAttribute> Attributes;

	~FAttributesSet() {};

};

USTRUCT(BlueprintType)
struct FAttributesSetModifier : public FAttributesSet
{
	GENERATED_BODY()


public:
	//default constructor
	FAttributesSetModifier()
	{
		Guid = FGuid::NewGuid();
	}

	UPROPERTY(BlueprintReadOnly, Category = ARS)
		FGuid Guid;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ARS)
		EModifierType ModType;

	FORCEINLINE	bool operator==(const FAttributesSetModifier &Other) const
	{
		return this->Guid == Other.Guid;
	}

	FORCEINLINE	bool operator!=(const FAttributesSetModifier &Other) const
	{
		return this->Guid != Other.Guid;
	}

	~FAttributesSetModifier() {};

};

USTRUCT(BlueprintType)
struct FStatisticModifier : public FTableRowBase
{
	GENERATED_BODY()

public:

	FStatisticModifier() {};

	FStatisticModifier( FGameplayTag tag,  float value)
	{
		Statistic = tag;
		Value = value;
	};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ARS)
		FGameplayTag Statistic;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ARS)
		float Value;
};

USTRUCT(BlueprintType)
struct FAttributeInfluence : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = ARS)
		UCurveFloat* CurveValue;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = ARS)
		FGameplayTag TargetParameter;
};

USTRUCT(BlueprintType)
struct FStatInfluence : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = ARS)
		UCurveFloat* CurveRegenValue;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = ARS)
		UCurveFloat* CurveMaxValue;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = ARS)
		FGameplayTag TargetStat;
};

USTRUCT(BlueprintType)
struct FGenerationRule : public FTableRowBase
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = ARS)
		TArray<FStatInfluence> InfluencedStatistics;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = ARS)
		TArray<FAttributeInfluence> InfluencedParameters;

};

USTRUCT(BlueprintType)
struct FAttributesByLevel : public FTableRowBase
{
	GENERATED_BODY()

public:

	UPROPERTY(EditDefaultsOnly, Category = ARS)
		TMap<FGameplayTag, UCurveFloat*> PrimaryStatByLevelCurves;

};

USTRUCT(BlueprintType)
struct FTimedAttributeSetModifier : public FTableRowBase
{
	GENERATED_BODY()

public:

	FTimedAttributeSetModifier() {};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ACF)
	FAttributesSetModifier modifier;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ACF)
	float duration;

};

UCLASS()
class ADVANCEDRPGSYSTEM_API UARSStatisticsData : public UObject
{
	GENERATED_BODY()
	
public: 

	
	
};
