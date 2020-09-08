//
// (C) Copyright by Techmo sp. z o. o., 2019. All rights reserved.
//
#include "StkDiagnostics.h"
#include "StkCommon.h"
#include "StkGameModule.h"

#include "Internationalization/Regex.h"
#include "Sound/SoundCue.h"
#include "Components/AudioComponent.h"
#include "AudioDevice.h"
#include "ActiveSound.h"
#include "CoreGlobals.h"

#include "Misc/ConfigCacheIni.h"

namespace
{
	bool IsSoundToolKitPluginEnabled(EAudioPlugin PluginType)
	{
		const TCHAR* ParamName;
		switch (PluginType)
		{
		case EAudioPlugin::SPATIALIZATION:
			ParamName = TEXT("SpatializationPlugin");
			break;
		case EAudioPlugin::REVERB:
			ParamName = TEXT("ReverbPlugin");
			break;
		case EAudioPlugin::OCCLUSION:
			ParamName = TEXT("OcclusionPlugin");
			break;
		default:
			return false;
		}

		GConfig->Flush(false, GEngineIni);

		FString PluginName;
		GConfig->GetString(
			TEXT("/Script/WindowsTargetPlatform.WindowsTargetSettings"),
			ParamName,
			PluginName,
			GEngineIni
		);

		return PluginName == SoundToolKit::Utils::GetGameModule().GetAudioPluginDisplayName(PluginType);
	}

	bool OcclusionSettingsAttached(const FSoundAttenuationPluginSettings& PluginSettings)
	{
		return PluginSettings.OcclusionPluginSettingsArray.FindByPredicate([](UOcclusionPluginSourceSettingsBase* Settings)
			{ return Cast<UStkOcclusionSourceSettings>(Settings); }) != nullptr;
	}

	int GetGlobalSettingMaxChannelsCount()
	{
		FString ConfigFilePath = FPaths::Combine(FPaths::ProjectConfigDir(), TEXT("DefaultEngine.ini"));
		GConfig->Flush(true, ConfigFilePath);

		FString QualityLevels;
		GConfig->GetString(
			TEXT("/Script/Engine.AudioSettings"),
			TEXT("+QualityLevels"),
			QualityLevels,
			ConfigFilePath
		);

		const int32 FromMaxChannelsIndex = QualityLevels.Find(TEXT("MaxChannels="));

		if (FromMaxChannelsIndex == INDEX_NONE)
		{
			return 0;
		}

		const FString FromMaxChannelsSubString = QualityLevels.RightChop(FromMaxChannelsIndex);
		const FRegexPattern FirstDigitPattern(TEXT("[0-9]+"));
		FRegexMatcher Matcher(FirstDigitPattern, FromMaxChannelsSubString);

		if (Matcher.FindNext())
		{
			FString MaxChannelsStr = FromMaxChannelsSubString.RightChop(Matcher.GetMatchBeginning());
			MaxChannelsStr = MaxChannelsStr.LeftChop(FromMaxChannelsSubString.Len() - Matcher.GetMatchEnding());
			return FCString::Atoi(*MaxChannelsStr);
		}
		
		return 0;
	}

	int GetPlatformSettingMaxChannelsCount()
	{
		GConfig->Flush(false, GEngineIni);

		int32 AudioMaxChannels;
		GConfig->GetInt(
			TEXT("/Script/WindowsTargetPlatform.WindowsTargetSettings"),
			TEXT("AudioMaxChannels"),
			AudioMaxChannels,
			GEngineIni
		);

		return AudioMaxChannels;
	}
}

FStatusIndicator::FStatusIndicator()
	: StkStatusIndicator(nullptr)
{
}

FStatusIndicator::FStatusIndicator(SoundToolKit::FStkStatusIndicator* StatusIndicator, const FString& ValueIn)
	: StkStatusIndicator(StatusIndicator)
	, Name(StkStatusIndicator->ShortName())
	, Type(StkStatusIndicator->Type())
	, Description(StkStatusIndicator->Description())
	, Value(ValueIn)
{
}

void FStatusIndicator::Update()
{
	Value = StkStatusIndicator->Value();
}

FActiveSoundDiagnostic::FActiveSoundDiagnostic() = default;

FActiveSoundDiagnostic::FActiveSoundDiagnostic(const FActiveSound* ActiveSound, const bool bAllPluginsSetToSoundToolKit)
	: Sample(ActiveSound->GetAudioComponentName())
	, Position(ActiveSound->LastLocation.ToString())
{
	UAudioComponent* AudioComponent = UAudioComponent::GetAudioComponentFromID(ActiveSound->GetAudioComponentID());
	if (AudioComponent)
	{
		if (AActor* Owner = AudioComponent->GetOwner())
		{
			Actor = Owner->GetActorLabel();
		}
	}

	auto SetSoundProcessIndicators = [&](const FSoundAttenuationSettings& Settings)
	{
		bSpatializationEnabled = Settings.bSpatialize;

		bProcessedBySoundToolKit = bAllPluginsSetToSoundToolKit &&
			ActiveSound->bAllowSpatialization &&
			Settings.SpatializationAlgorithm == ESoundSpatializationAlgorithm::SPATIALIZATION_HRTF &&
			Settings.bEnableOcclusion &&
			OcclusionSettingsAttached(Settings.PluginSettings);

		bProcessedByUnrealEngine = !bAllPluginsSetToSoundToolKit ||
			Settings.SpatializationAlgorithm != ESoundSpatializationAlgorithm::SPATIALIZATION_HRTF ||
			Settings.bAttenuate ||
			Settings.bAttenuateWithLPF ||
			Settings.bEnableListenerFocus;
	};

	if (AudioComponent && AudioComponent->bOverrideAttenuation)
	{
		SetSoundProcessIndicators(AudioComponent->AttenuationOverrides);
	}
	else if (AudioComponent && AudioComponent->AttenuationSettings)
	{
		SetSoundProcessIndicators(ActiveSound->AttenuationSettings);
	}
	else if (USoundCue* Sound = Cast<USoundCue>(ActiveSound->GetSound()))
	{
		if (Sound->bOverrideAttenuation)
		{
			SetSoundProcessIndicators(Sound->AttenuationOverrides);
		}
		else if (Sound->AttenuationSettings)
		{
			SetSoundProcessIndicators(Sound->AttenuationSettings->Attenuation);
		}
	}
	else
	{
		SetSoundProcessIndicators(ActiveSound->AttenuationSettings);
	}
}

AStkDiagnostics::AStkDiagnostics()
	: bActiveSoundsDiagnostics(false)
	, StkControl(&SoundToolKit::Utils::GetGameModule().GetControl())
	, StkSoundSourceManager(&SoundToolKit::Utils::GetGameModule().GetSoundSourceManager()) 
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.SetTickFunctionEnable(true);
	PrimaryActorTick.bStartWithTickEnabled = true;

	bStkOcclusionPluginEnabled = IsSoundToolKitPluginEnabled(EAudioPlugin::OCCLUSION);
	bStkSpatializationPluginEnabled = IsSoundToolKitPluginEnabled(EAudioPlugin::SPATIALIZATION);
	bStkReverbPluginEnabled = IsSoundToolKitPluginEnabled(EAudioPlugin::REVERB);

	GlobalMaxChannelsCount = GetGlobalSettingMaxChannelsCount();
	PlatformMaxChannelsCount = GetPlatformSettingMaxChannelsCount();
}

void AStkDiagnostics::BeginPlay()
{
	SubscribeToStatusIndicators();

	Super::BeginPlay();
}

void AStkDiagnostics::EndPlay(const EEndPlayReason::Type Type)
{
	IndicatorAddedSubscription->disconnect();
	IndicatorRemovedSubscription->disconnect();

	Super::EndPlay(Type);
}

void AStkDiagnostics::Tick(float DeltaSeconds)
{
	for (TPair<FString, FStatusIndicator>& Element : StatusIndicators)
	{
		Element.Value.Update();
	}
	
	ActiveSoundsDiagnostics.Empty();
	if (bActiveSoundsDiagnostics)
	{
		int32 ActiveSoundsCounter = 0;
		int32 NonActorSourcesCounter = 0;
		TArray<FAudioDevice*> AudioDevices = GEngine->GetAudioDeviceManager()->GetAudioDevices();
		for (FAudioDevice* AudioDevice : AudioDevices)
		{
			if (!AudioDevice)
			{
				continue;
			}

			TArray<FActiveSound*> ActiveSounds = AudioDevice->GetActiveSounds();
			for (FActiveSound* ActiveSound : ActiveSounds)
			{
				++ActiveSoundsCounter;

				if (ActiveSound->GetAudioComponentUserID() == SoundToolKit::Utils::GetAudioSinkName())
				{
					continue;
				}

				FString Key = ActiveSound->GetAudioComponentID() ? ActiveSound->GetOwnerName() : TEXT("FireAndForgetSound_") + FString::FromInt(NonActorSourcesCounter++);
				ActiveSoundsDiagnostics.Emplace(Key, FActiveSoundDiagnostic(ActiveSound,
					bStkOcclusionPluginEnabled && bStkSpatializationPluginEnabled && bStkReverbPluginEnabled));
			}
		}

		if (GlobalMaxChannelsCount)
		{
			const int32 MaxChannelsCount = PlatformMaxChannelsCount ?
				FMath::Min(GlobalMaxChannelsCount, PlatformMaxChannelsCount) : GlobalMaxChannelsCount;
			if (MaxChannelsCount > 0 && ActiveSoundsCounter > MaxChannelsCount)
			{
				STK_LOG(Error, TEXT("Number of active sounds (%d) exceeds the 'Max Channels' setting value (%d)."), ActiveSoundsCounter, MaxChannelsCount);
			}
		}
	}

	Super::PostEditChange();
}

void AStkDiagnostics::SubscribeToStatusIndicators()
{
	IndicatorAddedSubscription = StkControl->SubscribeStatusIndicatorAdded(
		[&StkStatusIndicators{ StkStatusIndicators }, &StatusIndicatorsMap{ StatusIndicators }](stk::IIndicator& StatusIndicatorIn, FString Value)
	{
		int32 Index = StkStatusIndicators.Emplace(MakeUnique<SoundToolKit::FStkStatusIndicator>(StatusIndicatorIn));

		FStatusIndicator& StatusIndicator = StatusIndicatorsMap.Emplace(
			StkStatusIndicators[Index]->Name(),
			FStatusIndicator(StkStatusIndicators[Index].Get(), Value));
	});

	IndicatorRemovedSubscription = StkControl->SubscribeStatusIndicatorRemoved(
		[&StkStatusIndicators{ StkStatusIndicators }, &StatusIndicatorsMap{ StatusIndicators }](stk::IIndicator& StatusIndicator)
	{
		for (int32 i = 0; i < StkStatusIndicators.Num(); ++i)
		{
			if (&StkStatusIndicators[i]->Native() == &StatusIndicator)
			{
				StatusIndicatorsMap.Remove(StkStatusIndicators[i]->Name());
				StkStatusIndicators.RemoveAt(i);
				
				break;
			}
		}
	});
}
