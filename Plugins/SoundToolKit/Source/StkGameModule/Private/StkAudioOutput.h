//
// (C) Copyright by Techmo sp. z o. o., 2019. All rights reserved.
//
#pragma once

namespace stk
{
	class IAudioOutput;
}

namespace SoundToolKit
{
	/// <summary>
	/// Class used to get samples and manage parameters of audio output.
	/// </summary>
	class FStkAudioOutput
	{
	public:
		FStkAudioOutput(stk::IAudioOutput& AudioOutput);
		~FStkAudioOutput();

		float GetMasterVolume();
		void SetMasterVolume(float volume);

		void EnableHrtf();
		void DisableHrtf();
		bool IsHrtfEnabled() const;

		uint32 ChannelCount() const;
		uint32 SampleRate() const;

		/// <summary>
		/// Prepares the STK audio engine for rendering: allocates internal resources, buffers etc.
		/// </summary>
		/// <param name="ChannelCount">Output channel count</param>
		/// <param name="SampleRate">Output sample rate</param>
		/// <param name="BufferLength">Length of the interleaved output buffer</param>
		void Prepare(const uint32 ChannelCount, const uint32 SampleRate, const uint32 BufferLength);

		/// <summary>
		/// Used to get rendered samples from the engine.
		/// </summary>
		/// <param name="OutputBuffer">Mono (interleaved) buffer where the samples will be placed</param>
		void RenderInto(Audio::AlignedFloatBuffer& OutputBuffer);

	private:
		void SetSampleRate(const uint32 SampleRate);
		void SetOutputSpeakerType(const uint32 ChannelCount);
		// Should be called after SetOutputSpeakerType()
		void PrepareForRender(const uint32 BufferLength);

		stk::IAudioOutput& StkAudioOutput;

		uint32 CurrentSampleRate;
		uint32 CurrentChannelCount;
		uint32 MaxBufferLengthPerChannel;
	};
}
