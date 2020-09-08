//
// (C) Copyright by Techmo sp. z o. o., 2019. All rights reserved.
//
#include "StkAudioOutput.h"
#include "StkCommon.h"

THIRD_PARTY_INCLUDES_START
#include <stk/IAudioOutput.h>
THIRD_PARTY_INCLUDES_END

#include "DSP/BufferVectorOperations.h"

namespace SoundToolKit
{
	FStkAudioOutput::FStkAudioOutput(stk::IAudioOutput& AudioOutput)
		: StkAudioOutput(AudioOutput)
		, CurrentSampleRate(0)
		, CurrentChannelCount(0)
		, MaxBufferLengthPerChannel(0)
	{
	}

	FStkAudioOutput::~FStkAudioOutput() = default;

	uint32 FStkAudioOutput::ChannelCount() const
	{
		return CurrentChannelCount;
	}

	uint32 FStkAudioOutput::SampleRate() const
	{
		return CurrentSampleRate;
	}

	float FStkAudioOutput::GetMasterVolume()
	{
		return StkAudioOutput.masterVolume();
	}

	void FStkAudioOutput::SetMasterVolume(float volume)
	{
		StkAudioOutput.setMasterVolume(volume);
	}

	void FStkAudioOutput::EnableHrtf()
	{
		StkAudioOutput.enableHrtf();
	}

	void FStkAudioOutput::DisableHrtf()
	{
		StkAudioOutput.disableHrtf();
	}

	bool FStkAudioOutput::IsHrtfEnabled() const
	{
		return StkAudioOutput.isHrtfEnabled();
	}

	void FStkAudioOutput::Prepare(const uint32 ChannelCount, const uint32 SampleRate, const uint32 BufferLength)
	{
		if (IsInAudioThread())
		{
			SetOutputSpeakerType(ChannelCount);
			SetSampleRate(SampleRate);
			PrepareForRender(BufferLength);
		}
		else
		{
			FGraphEventRef Task = FFunctionGraphTask::CreateAndDispatchWhenReady([&]
			{
				SetOutputSpeakerType(ChannelCount);
				SetSampleRate(SampleRate);
				PrepareForRender(BufferLength);
			}, TStatId(), nullptr, ENamedThreads::AudioThread);
			FTaskGraphInterface::Get().WaitUntilTaskCompletes(Task);
		}
	}

	void FStkAudioOutput::RenderInto(Audio::AlignedFloatBuffer& OutputBuffer)
	{
		const uint32 BufferLengthPerChannel = OutputBuffer.Num() / CurrentChannelCount;
		PrepareForRender(BufferLengthPerChannel);
		StkAudioOutput.render(BufferLengthPerChannel);
		stk::AudioBufferInterleavedView view = StkAudioOutput.getSamplesInterleaved();

		FMemory::Memcpy(OutputBuffer.GetData(), view.data(), sizeof(float) * OutputBuffer.Num());
	}

	void FStkAudioOutput::SetSampleRate(const uint32 SampleRate)
	{
		if (SampleRate != CurrentSampleRate)
		{
			StkAudioOutput.setSamplingRate(static_cast<float>(SampleRate));

			CurrentSampleRate = SampleRate;
		}
	}

	void FStkAudioOutput::SetOutputSpeakerType(const uint32 ChannelCount)
	{
		if (ChannelCount != CurrentChannelCount)
		{
			StkAudioOutput.setSpeakersConfiguration(Utils::GetSpeakerConfiguration(ChannelCount));

			CurrentChannelCount = ChannelCount;
		}
	}

	void FStkAudioOutput::PrepareForRender(const uint32 BufferLengthPerChannel)
	{
		if (BufferLengthPerChannel > MaxBufferLengthPerChannel)
		{
			// prepareForRender() needs a maximum value
			StkAudioOutput.prepareForRender(BufferLengthPerChannel);

			MaxBufferLengthPerChannel = BufferLengthPerChannel;
		}
	}
}
