// Copyright (C) Pakyman Prod. 2020. All Rights Reserved.

#include "ARSStatisticsComponent.h"
#include "ARSFunctionLibrary.h"
#include "ARSStatisticsData.h"
#include "Net/UnrealNetwork.h"
#include <Curves/CurveFloat.h>
#include <Engine/World.h>
#include <Kismet/GameplayStatics.h>
#include <Kismet/KismetSystemLibrary.h>
#include <TimerManager.h>


// Sets default values for this component's properties
UARSStatisticsComponent::UARSStatisticsComponent() {
  // Set this component to be initialized when the game starts, and to be ticked
  // every frame.  You can turn these features off to improve performance if you
  // don't need them.
  PrimaryComponentTick.bCanEverTick = false;

  SetIsReplicatedByDefault(true);
  // ...
}

void UARSStatisticsComponent::GetLifetimeReplicatedProps(
    TArray<FLifetimeProperty> &OutLifetimeProps) const {
  Super::GetLifetimeReplicatedProps(OutLifetimeProps);

  DOREPLIFETIME(UARSStatisticsComponent, AttributeSet);
  DOREPLIFETIME(UARSStatisticsComponent, CurrentExps);
}

void UARSStatisticsComponent::InitializeAttributeSet() {
  if (GetOwner()->HasAuthority()) {
    InitilizeLevelData();

    Internal_InitializeStats();

    StartRegeneration();
  }
}

// Called when the game starts
void UARSStatisticsComponent::BeginPlay() { 

	Super::BeginPlay();
	
	if (bAutoInitialize) {
		InitializeAttributeSet();
	}
}

// Called every frame
void UARSStatisticsComponent::TickComponent(
    float DeltaTime, ELevelTick TickType,
    FActorComponentTickFunction *ThisTickFunction) {
  Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UARSStatisticsComponent::RegenerateStat() {
  for (auto &elem : AttributeSet.Statistics) {
    if (elem.HasRegeneration) {
      if (regenDelay.Contains(elem.StatType)) {
        FDateTime *before = regenDelay.Find(elem.StatType);
        if (before) {
          FTimespan delay = FDateTime::Now() - *before;
          if (delay.GetSeconds() > elem.RegenDelay) {
            regenDelay.Remove(elem.StatType);
          } else
            continue;
        }
      }
      FStatisticModifier _mod;
      _mod.Statistic = elem.StatType;
      _mod.Value = elem.RegenValue * RegenerationTimeInterval;
      Internal_ModifyStat(_mod, false);
    }
  }
}

void UARSStatisticsComponent::AddAttributeSetModifier_Implementation(
    const FAttributesSetModifier &_modifier) {

  if (_modifier.Statistics.Num() == 0 &&
      _modifier.Attributes.Num() == 0 &&
      _modifier.Parameters.Num() == 0) {
    return;
  }

  if (!bIsInitialized) {
	  _storedUnactiveModifiers.Add(_modifier);
	  return;
  }


  switch (_modifier.ModType) {
  case EModifierType::EAdditive:
    Internal_AddModifier(_modifier);
    break;
  case EModifierType::EPercentage:
    FAttributesSetModifier _newmod =
        CreateAdditiveAttributeSetModifireFromPercentage(_modifier);
    Internal_AddModifier(_newmod);
    break;
  }
}

bool UARSStatisticsComponent::AddAttributeSetModifier_Validate(
    const FAttributesSetModifier &_modifier) {
  return true;
}

void UARSStatisticsComponent::Internal_AddModifier(
    const FAttributesSetModifier &_modifier) {


  _activeModifiers.Add(_modifier);

  GenerateStats();
}

void UARSStatisticsComponent::GenerateStats() {
	
	_currentValues.Empty();
  for (FStatistic stat : AttributeSet.Statistics) {
    _currentValues.Add(stat);
  }

  CalcualtePrimaryStats();
  GenerateSecondaryStat();

  for (FStatistic &stat : AttributeSet.Statistics) {
    FStatistic *oldStat = _currentValues.FindByKey(stat);
    if (oldStat)
      stat.CurrentValue = UARSFunctionLibrary::GetNewCurrentValueForNewMaxValue(
          oldStat->CurrentValue, oldStat->MaxValue, stat.MaxValue);
  }

  OnAttributeSetModified.Broadcast();
}

void UARSStatisticsComponent::Internal_ModifyStat(
    const FStatisticModifier &StatMod, bool bResetDelay) {
  if (!bIsInitialized)
    return;

  FStatistic *_stat = AttributeSet.Statistics.FindByKey(StatMod.Statistic);

  if (_stat) {
    _stat->CurrentValue +=
        StatMod.Value; // *GetConsumptionMultiplierByStatistic(_stat->StatType);
    _stat->CurrentValue =
        FMath::Clamp(_stat->CurrentValue, 0.f, _stat->MaxValue);
    if (bResetDelay && _stat->HasRegeneration && _stat->RegenDelay > 0.f) {
      regenDelay.Add(_stat->StatType, FDateTime::Now());
    }
    OnAttributeSetModified.Broadcast();

    if (FMath::IsNearlyZero(_stat->CurrentValue)) {
        OnStatisiticReachesZero.Broadcast(_stat->StatType);
    }
  }
}

void UARSStatisticsComponent::CalcualtePrimaryStats() {
  AttributeSet.Attributes = _baseAttributeSet.Attributes;

  for (FAttributesSetModifier _modifier : _activeModifiers) {
    for (auto &_att : _modifier.Attributes) {
      ensure(UARSFunctionLibrary::IsValidAttributeTag(_att.AttributeType));
      if (UARSFunctionLibrary::IsValidAttributeTag(_att.AttributeType)) {
        FAttribute *_originalatt = AttributeSet.Attributes.FindByKey(_att);
        if (_originalatt) {
          *(_originalatt) = *(_originalatt) + _att;
        }
      }
    }
  }
}

void UARSStatisticsComponent::CalcualteSecondaryStats() {
  for (FAttributesSetModifier _modifier : _activeModifiers) {
    for (auto &_att : _modifier.Parameters) {
      ensure(UARSFunctionLibrary::IsValidParameterTag(_att.AttributeType));
      if (UARSFunctionLibrary::IsValidParameterTag(_att.AttributeType)) {
        FAttribute *_originalatt = AttributeSet.Parameters.FindByKey(_att);
        if (_originalatt) {
          *(_originalatt) = *(_originalatt) + _att;
        } else {
          AttributeSet.Parameters.Add(_att);
        }
      }
    }

    for (auto &_att : _modifier.Statistics) {
      ensure(UARSFunctionLibrary::IsValidStatisticTag(_att.StatType));
      if (UARSFunctionLibrary::IsValidStatisticTag(_att.StatType)) {
        FStatistic *_originalatt = AttributeSet.Statistics.FindByKey(_att);
        if (_originalatt) {
          *(_originalatt) = *(_originalatt) + _att;
        } else {
          AttributeSet.Statistics.Add(_att);
        }
      }
    }
  }
}

FAttributesSetModifier
UARSStatisticsComponent::CreateAdditiveAttributeSetModifireFromPercentage(
    const FAttributesSetModifier &_modifier) {
  FAttributesSetModifier newatt;
  newatt.Guid = _modifier.Guid;

  newatt.ModType = EModifierType::EAdditive;

  for (auto &_att : _modifier.Attributes) {
    FAttribute *_originalatt = AttributeSet.Attributes.FindByKey(_att);
    if (_originalatt) {

      float newval = _originalatt->Value * _att.Value / 100.f;
      FAttribute _new(_att.AttributeType, newval);
      newatt.Attributes.AddUnique(_new);
    }
  }
  for (auto &_att : _modifier.Parameters) {
    FAttribute *_originalatt = AttributeSet.Parameters.FindByKey(_att);
    if (_originalatt) {

      float newval = _originalatt->Value * _att.Value / 100.f;
      FAttribute _new(_att.AttributeType, newval);
      newatt.Parameters.AddUnique(_new);
    }
  }
  for (auto &_att : _modifier.Statistics) {
    FStatistic *_originalatt = AttributeSet.Statistics.FindByKey(_att);
    if (_originalatt) {

      float newval = _originalatt->MaxValue * _att.MaxValue / 100.f;
      float newregenval = _originalatt->RegenValue * _att.RegenValue / 100.f;
      float newRegenDelay = _originalatt->RegenDelay * _att.RegenDelay / 100.f;
      FStatistic _new(_att.StatType, newval, newregenval, newRegenDelay);
      newatt.Statistics.AddUnique(_new);
    }
  }
  return newatt;
}

void UARSStatisticsComponent::GenerateSecondaryStat() {
  AttributeSet.Parameters = _baseAttributeSet.Parameters;
  AttributeSet.Statistics = _baseAttributeSet.Statistics;

  GenerateSecondaryStatFromCurrentPrimaryStat();

  CalcualteSecondaryStats();
}

void UARSStatisticsComponent::GenerateSecondaryStatFromCurrentPrimaryStat() {

  for (FAttribute _primaryatt : AttributeSet.Attributes) {
    FGenerationRule _rules =
        UARSFunctionLibrary::GetGenerationRuleByPrimaryAttributeType(
            _primaryatt.AttributeType);

    for (FAttributeInfluence _att : _rules.InfluencedParameters) {
      if (_att.CurveValue) {
        FAttribute *_targetAttribute =
            AttributeSet.Parameters.FindByKey(_att.TargetParameter);
        if (_targetAttribute) {
          _targetAttribute->Value +=
              _att.CurveValue->GetFloatValue(_primaryatt.Value);
        } else {
          float param = _att.CurveValue->GetFloatValue(_primaryatt.Value);
          FAttribute localatt = FAttribute(_att.TargetParameter, param);
          AttributeSet.Parameters.AddUnique(localatt);
        }
      }
    }

    for (FStatInfluence _stat : _rules.InfluencedStatistics) {

      if (_stat.CurveMaxValue) {
        FStatistic *_targetStat =
            AttributeSet.Statistics.FindByKey(_stat.TargetStat);
        if (_targetStat) {
          _targetStat->MaxValue +=
              _stat.CurveMaxValue->GetFloatValue(_primaryatt.Value);
        } else {
          float param = _stat.CurveMaxValue->GetFloatValue(_primaryatt.Value);
          FStatistic localstat = FStatistic(_stat.TargetStat, param, 0.f);
          AttributeSet.Statistics.AddUnique(localstat);
        }
      }
      FStatistic *_targetStat =
          AttributeSet.Statistics.FindByKey(_stat.TargetStat);
      if (_targetStat && _stat.CurveRegenValue) {
        _targetStat->RegenValue +=
            _stat.CurveRegenValue->GetFloatValue(_primaryatt.Value);
        _targetStat->HasRegeneration = _targetStat->RegenValue != 0.f;
      }
    }
  }
}

void UARSStatisticsComponent::StartRegeneration_Implementation() {
  if (!bIsRegenerationStarted && bCanRegenerateStatistics) {
    UWorld *_world = GetWorld();
    if (_world) {
      _world->GetTimerManager().SetTimer(
          RegenTimer, this, &UARSStatisticsComponent::RegenerateStat,
          RegenerationTimeInterval, true);
      bIsRegenerationStarted = true;
    }
  }
}

bool UARSStatisticsComponent::StartRegeneration_Validate() { return true; }

void UARSStatisticsComponent::StopRegeneration_Implementation() {
  if (bIsRegenerationStarted) {
    UWorld *_world = GetWorld();
    // Calling MyUsefulFunction after 5 seconds without looping
    _world->GetTimerManager().ClearTimer(RegenTimer);
    bIsRegenerationStarted = false;
  }
}

bool UARSStatisticsComponent::StopRegeneration_Validate() { return true; }

void UARSStatisticsComponent::AddExp_Implementation(int32 exp) {

	if (LevelingType == ELevelingType::ECantLevelUp){
		UE_LOG(LogTemp, Warning, TEXT("This Character can not level up! ARSStatisticsComponent"));
		return;
	}
  CurrentExps += exp;

  OnCurrentExpValueChanged.Broadcast(CurrentExps);
  if (CurrentExps >= ExpToNextLevel &&
      CharacterLevel < UARSFunctionLibrary::GetMaxLevel()) {
    int32 _remainingExps = CurrentExps - ExpToNextLevel;
    CurrentExps = 0;
	CharacterLevel++;
	InitilizeLevelData();

	switch (LevelingType)
	{
	case ELevelingType::EGenerateNewStatsFromCurves:
		Internal_InitializeStats();
		break;
	case ELevelingType::EAssignPerksManually:
		Perks += PerksObtainedOnLevelUp;
		break;
	default:
		UE_LOG(LogTemp, Error, TEXT("A character that cannot level, just leved! ARSStatisticsComponent"));
		break;
	}
    OnLevelUp(CharacterLevel, _remainingExps);
    AddExp(_remainingExps);
  }
}

bool UARSStatisticsComponent::AddExp_Validate(int32 exp) { return true; }

void UARSStatisticsComponent::RemoveAttributeSetModifier_Implementation(
    const FAttributesSetModifier &_modifier) {
  FAttributesSetModifier *_localmod = _activeModifiers.FindByKey(_modifier);
  if (_localmod) {

    _activeModifiers.RemoveSingle(*(_localmod));

    GenerateStats();
  }
}

bool UARSStatisticsComponent::RemoveAttributeSetModifier_Validate(
    const FAttributesSetModifier &_modifier) {
  return true;
}

void UARSStatisticsComponent::AddStatisticConsumptionMultiplier_Implementation(
    FGameplayTag statisticTag, float multiplier /*= 1.0f*/) {
  if (UARSFunctionLibrary::IsValidStatisticTag(statisticTag)) {
    StatisticConsumptionMultiplier.Add(statisticTag, multiplier);
  }
}

bool UARSStatisticsComponent::AddStatisticConsumptionMultiplier_Validate(
    FGameplayTag statisticTag, float multiplier /*= 1.0f*/) {
  return true;
}

float UARSStatisticsComponent::GetConsumptionMultiplierByStatistic (  FGameplayTag statisticTag) {
  if (UARSFunctionLibrary::IsValidStatisticTag(statisticTag)) {
    float *_mult = StatisticConsumptionMultiplier.Find(statisticTag);
    if (_mult) {
      return *(_mult);
    }
  }
  return 1.0f;
}

bool UARSStatisticsComponent::CheckCosts(
    const TArray<FStatisticModifier> &Costs)  {
  for (const FStatisticModifier _cost : Costs) {
    if (!CheckCost(_cost))
      return false;
  }
  return true;
}

bool UARSStatisticsComponent::CheckAttributesRequirements(
    const TArray<FAttribute> &Requirements) {
  for (FAttribute _att : Requirements) {
    if (!UARSFunctionLibrary::IsValidAttributeTag(_att.AttributeType)) {
      UE_LOG(LogTemp, Log,
             TEXT("Invalid Primary Attribute Tag!!! - "
                  "CheckPrimaryAttributeRequirements"));
      return false;
    }
    FAttribute *_localatt =
        AttributeSet.Attributes.FindByKey(_att.AttributeType);
    if (_localatt && _localatt->Value < _att.Value)
      return false;
  }
  return true;
}

bool UARSStatisticsComponent::CheckCost(const FStatisticModifier &Cost) {
  FStatistic *_stat = AttributeSet.Statistics.FindByKey(Cost.Statistic);
  if (_stat) {
    return _stat->CurrentValue >
           (Cost.Value * GetConsumptionMultiplierByStatistic(_stat->StatType));
  } else {
    UE_LOG(LogTemp, Warning,
           TEXT("Missing Statistic! - ARSStatistic Component"));
  }
  return false;
}

void UARSStatisticsComponent::ConsumeStatistics(
    const TArray<FStatisticModifier> &Costs) {
  for (const FStatisticModifier _cost : Costs) {
    FStatisticModifier _mod = _cost;
    _mod.Value *= -1;
    ModifyStat(_mod);
  }
}

void UARSStatisticsComponent::OnRep_AttributeSet() {
  OnAttributeSetModified.Broadcast();
}

void UARSStatisticsComponent::Internal_InitializeStats() {
  bIsInitialized = false;

  AttributeSet.Statistics.Empty();
  AttributeSet.Attributes.Empty();
  AttributeSet.Parameters.Empty();

  switch (StatsLoadMethod) {
  case EStatsLoadMethod::EUseDefaultsWithoutGeneration:
  case EStatsLoadMethod::EGenerateFromDefaultsPrimary:
    AttributeSet = DefaultAttributeSet;
    break;
  case EStatsLoadMethod::ELoadByLevel:
    AttributeSet.Attributes = GetPrimitiveAttributesForCurrentLevel();
    break;
  default:
    break;
  }

  _baseAttributeSet = AttributeSet;

  if (StatsLoadMethod != EStatsLoadMethod::EUseDefaultsWithoutGeneration) {
    GenerateStats();
  }

  bIsInitialized = true;

  for (FAttributesSetModifier _mod : _storedUnactiveModifiers) {
    AddAttributeSetModifier(_mod);
  }
  _storedUnactiveModifiers.Empty();
}

void UARSStatisticsComponent::InitilizeLevelData() {
  if (ExpForNextLevelCurve) {
    float _nextlevelexp = ExpForNextLevelCurve->GetFloatValue(CharacterLevel);
    ExpToNextLevel = FMath::TruncToInt(_nextlevelexp);
  }
}

void UARSStatisticsComponent::OnLevelUp_Implementation(int32 newlevel,
                                                       int32 _remainingExp) {
  CharacterLevel = newlevel;

  OnCharacterLevelUp.Broadcast(CharacterLevel);
}

bool UARSStatisticsComponent::OnLevelUp_Validate(int32 newlevel,
                                                 int32 _remainingExp) {
  return true;
}

void UARSStatisticsComponent::ModifyStatistic(FGameplayTag Stat, float value) {
  FStatisticModifier mod = FStatisticModifier(Stat, value);

  ModifyStat(mod);
}

float UARSStatisticsComponent::GetCurrentValueForStatitstic(
    FGameplayTag stat) const {

  if (!UARSFunctionLibrary::IsValidStatisticTag(stat)) {
    UE_LOG(LogTemp, Warning,
           TEXT("INVALID STATISTIC TAG -  -  ARSStatistic Component"));
    return 0.f;
  }

  const FStatistic *_stat = AttributeSet.Statistics.FindByKey(stat);

  if (_stat) {
    return _stat->CurrentValue;
  } else {
    UE_LOG(LogTemp, Warning,
           TEXT("Missing Statistic! -  -  ARSStatistic Component"));
  }
  return 0.f;
}

float UARSStatisticsComponent::GetMaxValueForStatitstic(
    FGameplayTag stat) const {
  if (!UARSFunctionLibrary::IsValidStatisticTag(stat)) {
    UE_LOG(LogTemp, Warning,
           TEXT("INVALID STATISTIC TAG -  -  ARSStatistic Component"));
    return 0.f;
  }

  const FStatistic *_stat = AttributeSet.Statistics.FindByKey(stat);

  if (_stat) {
    return _stat->MaxValue;
  } else {
    UE_LOG(LogTemp, Warning,
           TEXT("Missing Statistic! -  -  ARSStatistic Component"));
  }
  return 0.f;
}

float UARSStatisticsComponent::GetNormalizedValueForStatitstic(
    FGameplayTag stat) const {
  const float max = GetMaxValueForStatitstic(stat);
  const float value = GetCurrentValueForStatitstic(stat);

  if (max != 0.f) {
    return value / max;
  }
  UE_LOG(LogTemp, Warning,
         TEXT("Missing Statistic! -  -  ARSStatistic Component"));
  return 0.f;
}

float UARSStatisticsComponent::GetAttributeValue(FGameplayTag stat) const {
  if (!UARSFunctionLibrary::IsValidAttributeTag(stat)) {
    UE_LOG(LogTemp, Warning,
           TEXT("INVALID PRIMARY ATTRIBUTE TAG -  -  ARSStatistic Component"));
    return 0.f;
  }

  const FAttribute *_stat = AttributeSet.Attributes.FindByKey(stat);

  if (_stat) {
    return _stat->Value;
  }

  UE_LOG(LogTemp, Warning,
         TEXT("Missing  Primary Attribute! -  -  ARSStatistic Component"));

  return 0.f;
}

float UARSStatisticsComponent::GetParameterValue(FGameplayTag stat) const {
  if (!UARSFunctionLibrary::IsValidParameterTag(stat)) {
    UE_LOG(
        LogTemp, Warning,
        TEXT("INVALID SECONDARY ATTRIBUTE TAG -  -  ARSStatistic Component"));
    return 0.f;
  }

  const FAttribute *_stat = AttributeSet.Parameters.FindByKey(stat);

  if (_stat) {
    return _stat->Value;
  }

  UE_LOG(LogTemp, Warning,
         TEXT("Missing  Secondary Attribute! -  -  ARSStatistic Component"));

  return 0.f;
}

FAttributesSet UARSStatisticsComponent::GetCurrentAttributeSet() const {
  return AttributeSet;
}

int32 UARSStatisticsComponent::GetExpOnDeath() const {
  if(!CanLevelUp())
    return ExpToGiveOnDeath;

    if (ExpToGiveOnDeathByCurrentLevel) {
		  float expToGive = ExpToGiveOnDeathByCurrentLevel->GetFloatValue(CharacterLevel);
		  return FMath::TruncToInt(expToGive);
	}

	UE_LOG(LogTemp, Error, TEXT("Invalid ExpToGiveOnDeathByCurrentLevel Curve!"));
	return -1;
}

void UARSStatisticsComponent::AssignPerkToAttribute_Implementation(const FGameplayTag& attributeTag, int32 numPerks /*= 1*/)
{
	if (numPerks > Perks) {
		UE_LOG(LogTemp, Warning, TEXT("You don't have enough perks!"));
		return;
	}

	PermanentlyModifyAttribute(attributeTag, numPerks);
	Perks -= numPerks;
}

bool UARSStatisticsComponent::AssignPerkToAttribute_Validate(const FGameplayTag& attributeTag, int32 numPerks /*= 1*/)
{
	return true;
}

void UARSStatisticsComponent::PermanentlyModifyAttribute_Implementation(
    const FGameplayTag &attribute, float deltaValue /*= 1.0f*/) {
  const FAttribute *currValue =
      DefaultAttributeSet.Attributes.FindByKey(attribute);
  if (currValue) {
    FAttribute newValue(currValue->AttributeType,
                        currValue->Value + deltaValue);
    DefaultAttributeSet.Attributes.Remove(newValue);
    DefaultAttributeSet.Attributes.AddUnique(newValue);
    InitializeAttributeSet();
  }
}

bool UARSStatisticsComponent::PermanentlyModifyAttribute_Validate(
    const FGameplayTag &attribute, float value /*= 1.0f*/) {
  return true;
}

void UARSStatisticsComponent::ModifyStat_Implementation(
    const FStatisticModifier &StatMod) {
  Internal_ModifyStat(StatMod);
}

bool UARSStatisticsComponent::ModifyStat_Validate(
    const FStatisticModifier &StatMod) {
  return true;
}

TArray<FAttribute>
UARSStatisticsComponent::GetPrimitiveAttributesForCurrentLevel() {
  return Internal_GetPrimitiveAttributesForCurrentLevel(
      AttributesByLevelCurves);
}

// TArray<FAttribute>
// UARSStatisticsComponent::GetPrimitiveAttributesForCurrentClassAndLevel()
// {
// 	if (AttributesByClass)
// 	{
// 		FAttributesByLevel* _fabl = AttributesByClass->FindRow<
// FAttributesByLevel>(ClassName, TEXT("Class OF The Character"));
//
// 		if (_fabl)
// 		{
// 			return
// Internal_GetPrimitiveAttributesForCurrentLevel(*_fabl);
// 		}
// 		else
// 		{
// 			UE_LOG(LogTemp, Log, TEXT("Remember to add Class and Levels
// Table!"));
// 		}
//
// 	}
// 	else
// 	{
// 		UE_LOG(LogTemp, Log, TEXT("Remember to add Class and Levels
// Table!"));
// 	}
//
// 	return TArray<FAttribute>();
// }

TArray<FAttribute>
UARSStatisticsComponent::Internal_GetPrimitiveAttributesForCurrentLevel(
    FAttributesByLevel _attset) {
  TArray<FAttribute> _attributes;
  for (auto &localatt : _attset.PrimaryStatByLevelCurves) {

    if (localatt.Value) {
      FAttribute _item;
      _item.AttributeType = localatt.Key;
      _item.Value = localatt.Value->GetFloatValue(CharacterLevel);
      _attributes.AddUnique(_item);
    }
  }
  return _attributes;
}

void UARSStatisticsComponent::AddTimedAttributeSetModifier_Implementation(
    const FAttributesSetModifier &_modifier, float duration) {
  if (duration == 0.f)
    return;

  if (!_modifier.Attributes.IsValidIndex(0) &&
	  !_modifier.Parameters.IsValidIndex(0) &&
	  !_modifier.Statistics.IsValidIndex(0)) {
	  return;
  }


  Internal_AddModifier(_modifier);

  FTimerDelegate TimerDel;
  FTimerHandle TimerHandle;
  TimerDel.BindUFunction(this, FName("RemoveAttributeSetModifier"), _modifier);

  UWorld *_world = GetWorld();
  if (_world) {
    _world->GetTimerManager().SetTimer(TimerHandle, TimerDel, duration, false);
  }
}

bool UARSStatisticsComponent::AddTimedAttributeSetModifier_Validate(
    const FAttributesSetModifier &_modifier, float duration) {
  return true;
}

void UARSStatisticsComponent::ReinitializeAttributeSetFromNewDefault_Implementation(
        const FAttributesSet &newDefault) {
  DefaultAttributeSet = newDefault;

  InitializeAttributeSet();
}

bool UARSStatisticsComponent::ReinitializeAttributeSetFromNewDefault_Validate(
    const FAttributesSet &newDefault) {
  return true;
}

void UARSStatisticsComponent::SetNewLevelAndReinitialize_Implementation(uint8 newLevel) {
  CharacterLevel = newLevel;

  InitializeAttributeSet();
}

bool UARSStatisticsComponent::SetNewLevelAndReinitialize_Validate(uint8 newLevel) {
  return true;
}
