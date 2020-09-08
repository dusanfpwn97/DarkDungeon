//
// (C) Copyright by Techmo sp. z o. o., 2019. All rights reserved.
//
#include "StkSoundSource.h"
#include "StkCommon.h"
#include "IStkGameModule.h"
#include "StkCommandDispatcher.h"
#include "StkOcclusionSourceSettings.h"
#include "StkSpatializationSourceSettings.h"
#include "StkReverbSourceSettings.h"
#include "Curves/CurveFloat.h"

THIRD_PARTY_INCLUDES_START
#include <stk/ISourceSpatial.h>
#include <stk/IResourcesFactory.h>
#include <stk_ex/attenuation/PredefinedAttenuationFunctions.h>
THIRD_PARTY_INCLUDES_END

#include "Components/AudioComponent.h"
#include "GameFramework/Actor.h"

namespace
{
	Audio::AlignedFloatBuffer ExtractLeftChannel(const float* Buffer, const int32 NumChannels, const int32 Length)
	{
		Audio::AlignedFloatBuffer LeftChannel;
		LeftChannel.AddZeroed(Length / NumChannels);

		for (int32 i = 0, j = 0; i < Length; i += NumChannels, ++j)
		{
			LeftChannel[j] = Buffer[i];
		}

		return LeftChannel;
	};

	SoundToolKit::FStkSoundSource::AttenuationFunction ConvertAttenuation(FRuntimeFloatCurve AttenuationCurve, float MaxDistance, float Radius)
	{
		if (!AttenuationCurve.EditorCurveData.Keys.Num())
		{
			return [](float x) -> float { return 0.0f; };
		}

		return[Curve{ *AttenuationCurve.GetRichCurveConst() }, MaxDistance, Radius](float Distance) -> float
		{
			if (Distance > MaxDistance) // stk::MaxDistance = UE4::InnerRadius + UE4::Falloff
			{
				return 0.0f; // any distance exceeding MaxDistance will be clamped to 0 regardless of the curve value in MaxDistance
			}

			if (Distance <= Radius)
			{
				return 1.0f;
			}

			return FMath::Clamp(Curve.Eval((Distance - Radius) / (MaxDistance - Radius)), 0.0f, 1.0f); // UE4::Distance = stk::Distance - UE4::InnerRadius
		};
	}

	SoundToolKit::FStkSoundSource::AttenuationFunction ChooseCurve(EStkAttenuationFunction AttenuationType, FRuntimeFloatCurve AttenuationCurve, float MaxDistance, float Radius)
	{
		switch (AttenuationType)
		{
		case EStkAttenuationFunction::StkAttenuation_Linear:
			return [Radius, MaxDistance](float Distance) -> float
			{
				return stk_ex::attenuation::linear(Distance, Radius, MaxDistance);
			};
		case EStkAttenuationFunction::StkAttenuation_Nothing:
			return [](float) -> float
			{
				return stk_ex::attenuation::nothing();
			};
		case 	EStkAttenuationFunction::StkAttenuation_Inverse:
			return [Radius, MaxDistance](float Distance) -> float
			{
				return stk_ex::attenuation::inverse(Distance, Radius, MaxDistance);
			};
		case EStkAttenuationFunction::StkAttenuation_Logarithmic:
			return [Radius, MaxDistance](float Distance) -> float
			{
				return stk_ex::attenuation::logarithmic(Distance, Radius, MaxDistance);
			};
		case EStkAttenuationFunction::StkAttenuation_LineSource:
			return [Radius](float Distance) -> float
			{
				return stk_ex::attenuation::lineSource(Distance, Radius);
			};
		case EStkAttenuationFunction::StkAttenuation_PointSource:
			return [Radius](float Distance) -> float
			{
				return stk_ex::attenuation::pointSource(Distance, Radius);
			};
		case EStkAttenuationFunction::StkAttenuation_ReverseLog:
			return [Radius, MaxDistance](float Distance) -> float
			{
				return stk_ex::attenuation::reverseLog(Distance, Radius, MaxDistance);
			};
		case EStkAttenuationFunction::StkAttenuation_Custom:
			return ConvertAttenuation(AttenuationCurve, MaxDistance, Radius);
		default:
			checkf(false, TEXT("Uknown attenuation distance algorithm!"));
			return nullptr;
		}
	}
}

namespace SoundToolKit
{
	FStkSoundSource::FStkSoundSource(StkCommandDispatcher& CommandDispatcher, stk::SharedResource<stk::ISoundToolKit> Stk, stk::SharedResource<stk::ISourceSpatial> SoundSource, stk::SharedResource<stk::ISampleStreaming> Sample)
		: CommandDispatcher(CommandDispatcher)
		, StkSpatialSoundSource(SoundSource)
		, StkSample(Sample)
		, bAreFirstSamplesEnqueuedAlready(false)
		, Position(FVector::ZeroVector)
		, Rotation(FQuat::Identity)

	{
		CommandDispatcher.Execute([&]
		{
			StkPlayback = Stk->resourcesFactory().createPlayback(StkSample, StkSpatialSoundSource);
		});
	}

	FStkSoundSource::~FStkSoundSource()
	{
		CommandDispatcher.Enqueue([&StkSpatialSoundSource{ StkSpatialSoundSource }, &StkSample{ StkSample }]
		{
			StkSpatialSoundSource = nullptr;
			StkSample = nullptr;
		});
	}

	void FStkSoundSource::SetName(const FString& InName)
	{
		Name = InName;
	}

	const FString& FStkSoundSource::GetName() const
	{
		return Name;
	}

	void FStkSoundSource::Stream(const Audio::AlignedFloatBuffer& AudioBuffer, const int32 NumChannels)
	{
		if (NumChannels > 1)
		{
			LogTooManyChannelsWarning();

			Audio::AlignedFloatBuffer LeftChannel = ExtractLeftChannel(AudioBuffer.GetData(), NumChannels, AudioBuffer.Num());
			StkSample->enqueueSamples(stk::AudioBufferInterleavedView{ LeftChannel.GetData(), 1, static_cast<size_t>(LeftChannel.Num()) });
		}
		else
		{
			StkSample->enqueueSamples(stk::AudioBufferInterleavedView(AudioBuffer.GetData(), NumChannels, AudioBuffer.Num()));
		}
	}

	void FStkSoundSource::Stream(const float* Buffer, uint64 Length, const int32 NumChannels)
	{
		if (NumChannels > 1)
		{
			LogTooManyChannelsWarning();

			Audio::AlignedFloatBuffer LeftChannel = ExtractLeftChannel(Buffer, NumChannels, Length);
			StkSample->enqueueSamples(stk::AudioBufferInterleavedView{ LeftChannel.GetData(), 1, static_cast<size_t>(LeftChannel.Num()) });
		}
		else
		{
			StkSample->enqueueSamples(stk::AudioBufferInterleavedView(Buffer, NumChannels, Length));
		}
	}

	void FStkSoundSource::SetNameFromComponentID(uint64 AudioComponentID)
	{
		CommandDispatcher.Enqueue([this, AudioComponentID]
		{
			UAudioComponent* AudioComponent = UAudioComponent::GetAudioComponentFromID(AudioComponentID);
			if (AudioComponent)
			{
				SetName(AudioComponent->GetOwner()->GetName());
			}
		});
	}

	bool FStkSoundSource::HasName() const
	{
		return !Name.IsEmpty();
	}

	void FStkSoundSource::ResumePlayback()
	{
		CommandDispatcher.Enqueue([&StkPlayback{ StkPlayback }]{ StkPlayback->play(); });
	}

	void FStkSoundSource::Reset()
	{
		CommandDispatcher.Enqueue([&StkPlayback{ StkPlayback }]{ StkPlayback->pause(); });

		SetOcclusionProperties(NewObject<UStkOcclusionSourceSettings>());
		SetSpatializationProperties(NewObject<UStkSpatializationSourceSettings>());
		SetReverbProperties(NewObject<UStkReverbSourceSettings>());

		SetName(TEXT(""));
		bAreFirstSamplesEnqueuedAlready = false;
	}

	void FStkSoundSource::SetOcclusionProperties(UStkOcclusionSourceSettings* OcclusionSettings)
	{
		CommandDispatcher.Enqueue([&StkSoundSource{ StkSpatialSoundSource },
			EnableReflection{OcclusionSettings->bReflectionEnabled},
			EnableTransmission{OcclusionSettings->bTransmissionEnabled},
			EnableDiffraction{OcclusionSettings->bTransmissionEnabled}]
			{
				if (EnableReflection)
				{
					StkSoundSource->enableSpatialEffect(stk::SpatialEffectType::Reflection);
				}
				else
				{
					StkSoundSource->disableSpatialEffect(stk::SpatialEffectType::Reflection);
				}
				if (EnableTransmission)
				{
					StkSoundSource->enableSpatialEffect(stk::SpatialEffectType::Transmission);
				}
				else
				{
					StkSoundSource->disableSpatialEffect(stk::SpatialEffectType::Transmission);
				}

				if (EnableDiffraction)
				{
					StkSoundSource->enableSpatialEffect(stk::SpatialEffectType::Diffraction);
				}
				else
				{
					StkSoundSource->disableSpatialEffect(stk::SpatialEffectType::Diffraction);
				}
			});
	}

	void FStkSoundSource::SetSpatializationProperties(UStkSpatializationSourceSettings* SpatializationSettings)
	{
		CommandDispatcher.Enqueue([&StkSoundSource{ StkSpatialSoundSource },
			Attenuation{ SpatializationSettings->Attenuation },
			AttenuationCurve{ SpatializationSettings->CustomAttenuation },
			Radius{ SpatializationSettings->InnerRadius * 0.01f },
			MaxDistance{ SpatializationSettings->InnerRadius * 0.01f + SpatializationSettings->FallofDistance * 0.01f },
			UseHrtfSpatialization{ SpatializationSettings->bUseHrtfSpatialization }]
			{
				StkSoundSource->setAttenuation(
					ChooseCurve(Attenuation, AttenuationCurve, MaxDistance, Radius));

				if (UseHrtfSpatialization)
				{
					StkSoundSource->enableHrtfSpatialization();
				}
				else
				{
					StkSoundSource->disableHrtfSpatialization();
				}
			});
	}

	void FStkSoundSource::SetReverbProperties(UStkReverbSourceSettings* ReverbSettings)
	{
		CommandDispatcher.Enqueue([&StkSoundSource{ StkSpatialSoundSource },
			EnableReverb{ ReverbSettings->bReverbEnabled }]
			{
				if (EnableReverb)
				{
					StkSoundSource->enableReverberation();
				}
				else
				{
					StkSoundSource->disableReverberation();
				}
			});
	}

	void FStkSoundSource::SetPosition(const FVector& InPosition)
	{
		if (InPosition != Position)
		{
			CommandDispatcher.Enqueue([&StkSoundSource{ StkSpatialSoundSource }, StkPosition{ Utils::ConvertVector(InPosition) }]
				{
					StkSoundSource->setPosition(StkPosition);
				});

			Position = InPosition;
		}
	}

	const FVector& FStkSoundSource::GetPosition() const
	{
		return Position;
	}

	void FStkSoundSource::SetRotation(const FQuat& InRotation)
	{
		if (InRotation != Rotation)
		{
			CommandDispatcher.Enqueue([&StkSoundSource{ StkSpatialSoundSource }, StkRotation{ Utils::ConvertQuaternion(InRotation) }]
				{
					StkSoundSource->setOrientation(StkRotation);
				});

			Rotation = InRotation;
		}
	}

	void FStkSoundSource::SetTransform(const FVector& InPosition, const FQuat& InRotation)
	{
		if (InPosition != Position || InRotation != Rotation)
		{
			stk::vec3 StkPosition = Utils::ConvertVector(InPosition);
			stk::quaternion StkRotation = Utils::ConvertQuaternion(InRotation);

			CommandDispatcher.Enqueue([&StkSoundSource{ StkSpatialSoundSource }, StkPosition, StkRotation]
				{
					StkSoundSource->setTransform(StkPosition, StkRotation);
				});

			Position = InPosition;
			Rotation = InRotation;
		}
	}

	void FStkSoundSource::SetAttenuation(const FStkSoundSource::AttenuationFunction AttenuationCurve)
	{
		CommandDispatcher.Enqueue([&StkSoundSource{ StkSpatialSoundSource }, AttenuationCurve]
			{
				StkSoundSource->setAttenuation(AttenuationCurve);
			});
	}

	void FStkSoundSource::UseHrtfSpatialization(const bool Use)
	{
		CommandDispatcher.Enqueue([&StkSoundSource{ StkSpatialSoundSource }, Use]
			{
				if (Use)
				{
					StkSoundSource->enableHrtfSpatialization();
				}
				else
				{
					StkSoundSource->disableHrtfSpatialization();
				}
			});
	}

	void FStkSoundSource::LogTooManyChannelsWarning()
	{
		if (!bAreFirstSamplesEnqueuedAlready)
		{
			bAreFirstSamplesEnqueuedAlready = true;
			STK_LOG(Warning, TEXT("Sample has more than one channel. Ignoring all channels except left one."
				" Spatialization settings are not applied for this sound source. To improve sound immersion use mono samples only."));
		}
	}
}
