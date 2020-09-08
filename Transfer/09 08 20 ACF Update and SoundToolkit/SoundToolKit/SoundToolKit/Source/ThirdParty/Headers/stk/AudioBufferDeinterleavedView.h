///
/// \author Jakub Perek <perek@techmo.pl>
/// \date 01.10.2018
///
#ifndef STK__AUDIO_BUFFER_DEINTERLEAVED_VIEW__H
#define STK__AUDIO_BUFFER_DEINTERLEAVED_VIEW__H

#include <iterator>
#include <cstddef>

#include <stk/ArrayView.h>

namespace stk
{
	/// <summary>
	/// A class used as a medium to transfer raw audio data into the engine and out of the engine.
	/// It wraps an array of pointers to floating point buffers which hold values of a given channel.
	/// Each channel must be of equal length.
	/// </summary>
	class AudioBufferDeinterleavedView
	{

		// public sub-types
	public:

		/// <summary>
		/// A helper type to view contents of a given channel.
		/// </summary>
		using ChannelView = stk::ArrayView<float>;

		// public construction and destruction methods
	public:

		AudioBufferDeinterleavedView(const float* const* buffers, size_t channelsCount, size_t channelLength)
			: m_ext_buffers(buffers), m_channelsCount(channelsCount), m_channelLength(channelLength) {}

		AudioBufferDeinterleavedView(const AudioBufferDeinterleavedView&) = default;
		AudioBufferDeinterleavedView(AudioBufferDeinterleavedView&&) = default;

		AudioBufferDeinterleavedView& operator=(const AudioBufferDeinterleavedView&) = default;
		AudioBufferDeinterleavedView& operator=(AudioBufferDeinterleavedView&&) = default;

		~AudioBufferDeinterleavedView() = default;

		// public methods
	public:

		/// <returns>
		/// A view which allows to access individual samples for a given channel.
		/// </returns>
		ChannelView getChannel(size_t index) const { return ChannelView{ m_ext_buffers[index], m_channelLength }; }

		/// <returns>
		/// The number of channels.
		/// </returns>
		size_t channelsCount() const { return m_channelsCount; }

		/// <returns>
		/// The number of samples in each channel.
		/// Each channel has the same length.
		/// </returns>
		size_t channelLength() const { return m_channelLength; }

		/// <returns>
		/// The wrapped pointer.
		/// </returns>
		const float* const* data() const { return m_ext_buffers; }

		// private properties
	private:

		const float* const* m_ext_buffers;
		size_t m_channelsCount;
		size_t m_channelLength;
	};
}

#endif
