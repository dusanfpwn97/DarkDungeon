//
// (C) Copyright by Techmo sp. z o. o., 2019. All rights reserved.
//
#include "StkCommon.h"
#include <fstream>
#include <filesystem>
#include "StkGameModule.h"
#include "StkAcousticMaterial.h"
#include "StkProjectData.h"
#include "StkLog.h"

THIRD_PARTY_INCLUDES_START
#include <stk/Math.h>
#include <stk/SpeakersConfiguration.h>
#include <stk/StringView.h>
#include <stk_ex/utility/MeshFaceValidator.h>
THIRD_PARTY_INCLUDES_END

#include "Interfaces/IPluginManager.h"
#include "Misc/Paths.h"
#include "Misc/FileHelper.h"
#include "Modules/ModuleManager.h"
#include "Sound/SoundWave.h"

DEFINE_LOG_CATEGORY(LogSoundToolKit);

namespace
{
	FString SimplifyRelativePath(const FString& InPath)
	{
		if (FPaths::IsRelative(InPath))
		{
			const FString BaseDir = FPlatformProcess::BaseDir();
			FString Path = FPaths::ConvertRelativePathToFull(BaseDir, InPath);
			FPaths::MakePathRelativeTo(Path, *BaseDir);

			return Path;
		}
		else
		{
			return InPath;
		}
	}
}

namespace SoundToolKit
{
	namespace Utils
	{
		FString ConvertSnakeCaseToCamelCase(FString StringToConvert)
		{
			StringToConvert[0] = toupper(StringToConvert[0]);
			int32 UnderscoreIndex;
			while (StringToConvert.FindChar(TCHAR('_'), UnderscoreIndex))
			{
				if (UnderscoreIndex == StringToConvert.Len()-1)
				{
					StringToConvert.RemoveAt(UnderscoreIndex);
					return StringToConvert;
				}
				else
				{
					StringToConvert[UnderscoreIndex + 1] = toupper(StringToConvert[UnderscoreIndex + 1]);
					StringToConvert.RemoveAt(UnderscoreIndex);
				}
			}

			return StringToConvert;
		}

		stk::vec3 ConvertVector(const FVector& Vector)
		{
			return { -Vector.X / 100, Vector.Z / 100, Vector.Y / 100 };
		}

		FVector ConvertVector(const stk::vec3& Vector)
		{
			return { -Vector.x * 100, Vector.z * 100, Vector.y * 100 };
		}

		stk::quaternion ConvertQuaternion(const FQuat& Quaternion)
		{
			constexpr float HalfSqrt2 = 0.7071068f;
			const FQuat ConversionQuat{ 0, 0, - HalfSqrt2, HalfSqrt2 };

			FQuat Quat = ConversionQuat * Quaternion;

			return { Quat.W, Quat.Y, Quat.Z, Quat.X };
		}

		FString GetPluginPath()
		{
			static const FString PluginPath = SimplifyRelativePath(IPluginManager::Get().FindPlugin(TEXT("SoundToolKit"))->GetBaseDir());

			return PluginPath;
		}

		FString GetContentPath()
		{
			static const FString ContentPath = SimplifyRelativePath(IPluginManager::Get().FindPlugin(TEXT("SoundToolKit"))->GetContentDir());

			return ContentPath;
		}

		stk::SpeakersConfiguration GetSpeakerConfiguration(const uint32 ChannelCount, const bool UseHrtf)
		{
			switch (ChannelCount)
			{
			case 1:
				return stk::SpeakersConfiguration::Mono;
			case 2:
				return (UseHrtf ? stk::SpeakersConfiguration::Headphones : stk::SpeakersConfiguration::SpeakersStereo);
			case 6:
				return stk::SpeakersConfiguration::Speakers_5_1;
			case 8:
				return stk::SpeakersConfiguration::Speakers_7_1;
			default:
				return static_cast<stk::SpeakersConfiguration>(-1);
			}
		}

		const FName& GetAudioSinkName()
		{
			static const FName AudioSinkName(TEXT("SoundToolKit_AudioSink"));
			return AudioSinkName;
		}

		FStkGameModule& GetGameModule()
		{
			return FModuleManager::LoadModuleChecked<FStkGameModule>("StkGameModule");
		}

		TArray<std::byte> LoadDiffractionData(stk::SharedResource<stk::ISoundToolKit> StkAudio)
		{
			TArray<std::byte> binaryData;
			try
			{
				FString fullPath = FPaths::Combine(GetPluginPath(), TEXT("Resources"));
				fullPath = FPaths::Combine(fullPath, TEXT("diffraction_table_100_20.bin"));
				FFileHelper::LoadFileToArray(reinterpret_cast<TArray<uint8>&>(binaryData), *fullPath);
			}
			catch (...)
			{
				STK_LOG(Fatal, TEXT("Could not load engine diffraction data."))
			}
			return binaryData;
		}

		TArray<std::byte> LoadHrtfData(stk::SharedResource<stk::ISoundToolKit> StkAudio)
		{
			TArray<std::byte> binaryData;
			try
			{
				FString fullPath = FPaths::Combine(GetPluginPath(), TEXT("Resources"));
				fullPath = FPaths::Combine(fullPath, TEXT("bqc_hrtf.bin"));
				FFileHelper::LoadFileToArray(reinterpret_cast<TArray<uint8>&>(binaryData), *fullPath);
			}
			catch (...)
			{
				STK_LOG(Fatal, TEXT("Could not load engine HRTF data."))
			}
			return binaryData;
		}

		FString ShortName(const stk::StringView& name)
		{
			FString ShortName = TEXT("");

			for (auto i = name.rfind('.') + 1; i < name.length(); ++i)
			{
				ShortName.AppendChar(name[i]);
			}

			return ShortName;
		}
	}
}
