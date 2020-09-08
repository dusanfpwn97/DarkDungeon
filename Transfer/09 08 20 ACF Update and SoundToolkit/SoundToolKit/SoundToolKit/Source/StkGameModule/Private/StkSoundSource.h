//
// (C) Copyright by Techmo sp. z o. o., 2019. All rights reserved.
//
#pragma once

#include "StkAttenuation.h"

THIRD_PARTY_INCLUDES_START
#include <stk/SharedResource.h>
#include <stk/ISampleStreaming.h>
#include <stk/ISoundToolKit.h>
#include <stk/IPlayback.h>
#include <stk/ISource.h>
THIRD_PARTY_INCLUDES_END

#include "DSP/BufferVectorOperations.h"

namespace stk
{
	class ISourceSpatial;
	class ISampleStreaming;
}

class UStkOcclusionSourceSettings;
class UStkSpatializationSourceSettings;
class UStkReverbSourceSettings;

namespace SoundToolKit
{
	class StkCommandDispatcher;

	/// <summary>
	/// Manages a spatial sound source within SoundToolKit engine.
	/// </summary>
	class STKGAMEMODULE_API FStkSoundSource
	{
	public:
		FStkSoundSource(StkCommandDispatcher& CommandDispatcher, stk::SharedResource<stk::ISoundToolKit> Stk, stk::SharedResource<stk::ISourceSpatial> SoundSource, stk::SharedResource<stk::ISampleStreaming> Sample);

		FStkSoundSource(const FStkSoundSource&) = delete;
		FStkSoundSource& operator=(const FStkSoundSource&) = delete;
		FStkSoundSource(FStkSoundSource&&) = default;
		FStkSoundSource& operator=(FStkSoundSource&&) = default;

		virtual ~FStkSoundSource();

		/// <summary>
		/// A subtype for attenuation curves - a float(float) function.
		/// </summary>
		/// <param name="Distance">The distance to the center of the sound source.</param>
		using AttenuationFunction = TFunction<float(float Distance)>;

		void SetName(const FString& Name);

		const FString& GetName() const;

		/// <summary>
		/// Streams samples to STK engine.
		/// </summary>
		/// <param name="AudioBuffer">Mono buffer containing samples that source should emit.</param>
		/// <param name="NumChannels">Number of channels.</param>
		void Stream(const Audio::AlignedFloatBuffer& AudioBuffer, const int32 NumChannels);

		/// <summary>
		/// Streams samples to STK engine.
		/// </summary>
		/// <param name="Buffer">Mono buffer containing samples that source should emit.</param>
		/// <param name="Length">Number of samples.</param>
		/// <param name="NumChannels">Number of channels.</param>
		void Stream(const float* Buffer, uint64 Length, const int32 NumChannels);

		/// <summary>
		/// Sets the name of stk::SpatialSoundSource and its stk::StreamingSample within SoundToolKit engine to match the name of AudioComponent.
		/// </summary>
		/// <param name="AudioComponentID">ID of the AudioComponent.</param>
		void SetNameFromComponentID(uint64 AudioComponentID);

		/// <summary>
		/// Indicates whether this SoundSource has a name within SoundToolKit engine.
		/// </summary>
		/// <returns>True if this SoundSource has a name.</returns>
		bool HasName() const;
		
		void ResumePlayback();

		/// <summary>
		/// Brings back a given source to a state where it can be safely reused.
		/// <summary>
		void Reset();

		void SetOcclusionProperties(UStkOcclusionSourceSettings* OcclusionSettings);
		void SetSpatializationProperties(UStkSpatializationSourceSettings* SpatializationSettings);
		void SetReverbProperties(UStkReverbSourceSettings* ReverbSettings);

		void SetPosition(const FVector& InPosition);

		const FVector& GetPosition() const;

		/// <summary>
		/// Sets forward vector for this sound source.
		/// </summary>
		/// <param name="InRotation">The vector pointing forward from the source's POV</param>
		void SetRotation(const FQuat& InRotation);

		/// <summary>
		/// Sets the position and orientation for this sound source at once.
		/// </summary>
		/// <param name="InPosition">The position to which the source should be moved.</param>
		/// <param name="InRotation">The vector pointing forward from the source's POV.</param>
		void SetTransform(const FVector& InPosition, const FQuat& InRotation);

		/// <summary>
		/// Sets the shape of the attenuation curve for this sound source.
		/// </summary>
		/// <param name="AttenuationCurve">
		///	A function of float(float) where the argument is distance to the center of the sound source
		/// </param>
		void SetAttenuation(AttenuationFunction AttenuationCurve);

		/// <summary>
		/// Enables HRTF spatialization for this sound source
		/// </summary>
		/// <param name="Use"></param>
		void UseHrtfSpatialization(const bool Use);

	protected:
		StkCommandDispatcher& CommandDispatcher;
		stk::SharedResource<stk::ISourceSpatial> StkSpatialSoundSource;

	private:
		void LogTooManyChannelsWarning();

	private:
		stk::SharedResource<stk::ISampleStreaming> StkSample;
		stk::SharedResource<stk::IPlayback> StkPlayback;

		FString Name;
		bool bAreFirstSamplesEnqueuedAlready;
		FVector Position;
		FQuat Rotation;
	};
}
