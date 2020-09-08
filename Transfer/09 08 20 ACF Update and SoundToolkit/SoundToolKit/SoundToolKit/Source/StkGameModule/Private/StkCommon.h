//
// (C) Copyright by Techmo sp. z o. o., 2019. All rights reserved.
//
#pragma once

#include "StkLog.h"
#include "StkAttenuation.h"

THIRD_PARTY_INCLUDES_START
#include <stk/SharedResource.h>
#include <stk/ISoundToolKit.h>
THIRD_PARTY_INCLUDES_END

namespace stk
{
	struct vec3;
	struct quaternion;
	enum class SpeakersConfiguration;
	class AudioResources;
	class StringView;
}

class UStkAcousticMaterial;
class USoundWave;
class UStaticMesh;

namespace SoundToolKit
{
	class FStkGameModule;

	namespace Utils
	{
		/// <summary>
		/// Used to convert string from snake case to camel case.
		/// </summary>
		STKGAMEMODULE_API FString ConvertSnakeCaseToCamelCase(FString StringToConvert);

		/// <summary>
		/// Converts a 3D vector from UE to STK units (1.0f in UE is 1cm, 1.0f in STK is 1m), 
		/// as well as changes axis orientation (X, Y, Z) -> (-X, Z, Y).
		/// </summary>
		STKGAMEMODULE_API stk::vec3 ConvertVector(const FVector& Vector);

		/// <summary>
		/// Converts a 3D vector from STK to UE units (1.0f in UE is 1cm, 1.0f in STK is 1m), 
		/// as well as changes axis orientation (X, Y, Z) -> (-X, Z, Y).
		/// </summary>
		STKGAMEMODULE_API FVector ConvertVector(const stk::vec3& Vector);

		/// <summary>
		/// Converts a unit FVector to stk::vec3 by changing axis orientation (X, Y, Z) -> (-X, Z, Y), without converting units.
		/// </summary>
		STKGAMEMODULE_API stk::quaternion ConvertQuaternion(const FQuat& Quaternion);

		/// <summary>
		/// Used to get path of the plugin.
		/// </summary>
		STKGAMEMODULE_API FString GetPluginPath();

		/// <summary>
		/// Used to get path to the Content folder of the plugin.
		/// </summary>
		STKGAMEMODULE_API FString GetContentPath();

		/// <summary>
		/// Converts channel count into speaker configuration enum type used by STK engine.
		/// </summary>
		/// <param name="ChannelCount">Channel count to convert</param>
		/// <param name="UseHrtf">Whether stereo (2 channels) should be converted to Headphones or Speakers_2_0</param>
		STKGAMEMODULE_API stk::SpeakersConfiguration GetSpeakerConfiguration(const uint32 ChannelCount, const bool UseHrtf = true);

		/// <summary>
		/// Used to get a name of audio component that is used to render SoundToolKit audio.
		/// </summary>
		STKGAMEMODULE_API const FName& GetAudioSinkName();

		/// <summary>
		/// Gets StkGameModule.
		/// </summary>
		STKGAMEMODULE_API FStkGameModule& GetGameModule();

		/// <summary>
		/// Helper method for locating and loading STK diffraction data.
		/// </summary>
		STKGAMEMODULE_API TArray<std::byte> LoadDiffractionData(stk::SharedResource<stk::ISoundToolKit> StkAudio);

		/// <summary>
		/// Helper method for locating and loading STK HRTF data.
		/// </summary>
		STKGAMEMODULE_API TArray<std::byte> LoadHrtfData(stk::SharedResource<stk::ISoundToolKit> StkAudio);

		/// <summary>
		/// Converts full hierarchical names (ex. for status indicators, paramters) to its short version (substring from after the last dot).
		/// </summary>
		STKGAMEMODULE_API FString ShortName(const stk::StringView& name);
	}
}
