//
// (C) Copyright by Techmo sp. z o. o., 2019. All rights reserved.
//
#pragma once

#include "StkControl.h"
#include "StkIndicator.h"
#include "StkSoundSourceManager.h"

#include "GameFramework/Actor.h"

THIRD_PARTY_INCLUDES_START
#include <stk/UniqueResource.h>
#include <stk/IConnection.h>
THIRD_PARTY_INCLUDES_END

#include "StkDiagnostics.generated.h"

/// <summary>
/// Struct used to represent stk::StatusIndicator objects in the UE4 engine.
/// </summary>
USTRUCT()
struct FStatusIndicator
{
	GENERATED_BODY()

	FStatusIndicator();
	FStatusIndicator(SoundToolKit::FStkStatusIndicator* StatusIndicator, const FString& ValueIn);

	/// <summary>
	/// Updates Value property with current stk::StatusIndicator indication.
	/// </summary>
	void Update();

private:
	SoundToolKit::FStkStatusIndicator* StkStatusIndicator;

public:
	UPROPERTY(VisibleAnywhere, Category = "Indicator")
	FString Name;

	UPROPERTY()
	FString Type;

	UPROPERTY()
	FString Description;

	UPROPERTY(VisibleAnywhere, Category = "Indicator")
	FString Value;
};

/// <summary>
/// Struct used respresent hold sound source diagnostic data.
/// </summary>
USTRUCT()
struct FActiveSoundDiagnostic
{
	GENERATED_BODY()

	FActiveSoundDiagnostic();
	FActiveSoundDiagnostic(const struct FActiveSound* SoundSource, const bool bAllPluginsSetToSoundToolKit);

	/// Actor this sound source is attached to
	UPROPERTY(VisibleAnywhere, Category = "Active Sound")
	FString Actor;

	/// Sample played by this source
	UPROPERTY(VisibleAnywhere, Category = "Active Sound")
	FString Sample;

	/// Position of the sound source
	UPROPERTY(VisibleAnywhere, Category = "Active Sound")
	FString Position;

	/// Is sound spatialization enabled for this sound source
	UPROPERTY(VisibleAnywhere, Category = "Active Sound")
	bool bSpatializationEnabled{ false };

	/// Is this sound source currently processed by STK
	UPROPERTY(VisibleAnywhere, Category = "Active Sound")
	bool bProcessedBySoundToolKit{ false };

	/// Is this sound source currently processed by Unreal sound engine 
	UPROPERTY(VisibleAnywhere, Category = "Active Sound")
	bool bProcessedByUnrealEngine{ false };
};

/// An actor providing diagnostic information regarding SoundToolKit engine.
UCLASS(HideCategories = (Actor, Advanced, Input, Rendering, LOD, Replication, Collision, Cooking))
class AStkDiagnostics : public AActor
{
	GENERATED_BODY()

public:
	AStkDiagnostics();

	// AActor interface
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type) override;
	virtual void Tick(float DeltaSeconds) override;
	// End of AActor interface

	/// Property holding all SoundToolKit's status indicators to facilitate displaying them.
	/// Available only in PIE mode.
	UPROPERTY(Transient, VisibleAnywhere, Category = "Diagnostics")
	TMap<FString, FStatusIndicator> StatusIndicators;

	/// Enables sound sources diagnostics.
	/// Available only in PIE mode.
	UPROPERTY(EditAnywhere, Category = "Diagnostics")
	bool bActiveSoundsDiagnostics;

	/// Holds info about sound sources that are currently active on the scene.
	/// Available only in PIE mode.
	UPROPERTY(Transient, VisibleAnywhere, Category = "Diagnostics", meta = (EditCondition = "bActiveSoundsDiagnostics"))
	TMap<FString, FActiveSoundDiagnostic> ActiveSoundsDiagnostics;

private:
	void SubscribeToStatusIndicators();

	SoundToolKit::FStkControl* StkControl;
	SoundToolKit::FStkSoundSourceManager* StkSoundSourceManager;
	stk::UniqueResource<stk::IConnection> IndicatorAddedSubscription{nullptr};
	stk::UniqueResource<stk::IConnection> IndicatorRemovedSubscription{nullptr};
	TArray<TUniquePtr<SoundToolKit::FStkStatusIndicator>> StkStatusIndicators;

	bool bStkOcclusionPluginEnabled;
	bool bStkSpatializationPluginEnabled;
	bool bStkReverbPluginEnabled;

	int32 GlobalMaxChannelsCount;
	int32 PlatformMaxChannelsCount;
};
