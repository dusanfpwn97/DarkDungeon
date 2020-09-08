///
/// \author Jakub Perek <perek@techmo.pl>
/// \date 01.10.2018
///
#ifndef STK__AUDIO_BUFFER_INTERLEAVED_VIEW__H
#define STK__AUDIO_BUFFER_INTERLEAVED_VIEW__H

#include <cstddef>
#include <iterator>

namespace stk
{

	/// <summary>
	/// A class used as a medium to transfer raw audio data into the engine and out of the engine.
	/// It wraps a single array of floating point values, where samples for each channel are interleaved.
	/// For instance, for stereo the samples are stored {left[0], right[0], left[1], right[1], ...}
	/// Each channel must be of equal length.
	/// </summary>
	class AudioBufferInterleavedView
	{
		// public sub-types
	public:

		/// <summary>
		/// A view which allows to access individual samples for a given channel.
		/// <summary>
		class ChannelView;

		// public construction and destruction methods
	public:

		AudioBufferInterleavedView(const float* buffer, size_t channelsCount, size_t channelLength)
			: m_ext_buffer(buffer), m_channelsCount(channelsCount), m_channelLength(channelLength) {}

		AudioBufferInterleavedView(const AudioBufferInterleavedView&) = default;
		AudioBufferInterleavedView(AudioBufferInterleavedView&&) = default;

		AudioBufferInterleavedView& operator=(const AudioBufferInterleavedView&) = default;
		AudioBufferInterleavedView& operator=(AudioBufferInterleavedView&&) = default;

		~AudioBufferInterleavedView() = default;

		// public methods
	public:

		/// <returns>
		/// A view for a given channel.
		/// </returns>
		ChannelView getChannel(size_t index) const;

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
		/// The length of the wrapped array.
		/// </returns>
		size_t bufferLength() const { return m_channelLength * m_channelsCount; }

		/// <returns>
		/// The wrapped pointer.
		/// </returns>
		const float* data() const { return m_ext_buffer; }

		// private properties
	private:

		const float* m_ext_buffer;
		size_t m_channelsCount;
		size_t m_channelLength;
	};

	/// <summary>
	/// A helper class to view contents of a given channel.
	/// </summary>
	class AudioBufferInterleavedView::ChannelView
	{

		// public sub-types
	public:
		class const_iterator;

		// public construction and destruction methods
	public:

		ChannelView(const ChannelView&) = default;
		ChannelView(ChannelView&&) = default;

		ChannelView& operator=(const ChannelView&) = default;
		ChannelView& operator=(ChannelView&&) = default;

		~ChannelView() = default;

		// public methods
	public:

		const float& operator[](size_t index) const { return m_ext_buffer[index * m_step]; }
		
		/// <remarks>
		/// Each channel of a given AudioBufferInterleavedView will have the same length.
		/// </remarks>
		/// <returns>
		/// The number of samples in this channel.
		/// </returns>
		size_t size() const { return m_size; }

		const_iterator cbegin() const;
		const_iterator cend() const;

		const_iterator begin() const;
		const_iterator end() const;

		// private construction and destruction methods
	private:

		ChannelView(const float* buffer, size_t step, size_t size) : m_ext_buffer(buffer), m_step(step), m_size(size) {}

		// private properties
	private:

		const float* m_ext_buffer;
		size_t m_step;
		size_t m_size;

		// friend declarations
	private:

		friend AudioBufferInterleavedView;
	};

	inline AudioBufferInterleavedView::ChannelView AudioBufferInterleavedView::getChannel(size_t index) const
	{
		return { m_ext_buffer + index, m_channelsCount, m_channelLength };
	}

	class AudioBufferInterleavedView::ChannelView::const_iterator
	{

		// public sub-types
	public:

		using value_type = float;
		using reference = const float&;
		using pointer = const float*;
		using difference_type = ptrdiff_t;
		using iterator_category = std::random_access_iterator_tag;

		// public construction and destruction methods
	public:

		const_iterator() : m_pointer(nullptr), m_step(0) {};
		const_iterator(const float* pointer, size_t step) : m_pointer(pointer), m_step(static_cast<difference_type>(step)) {}

		const_iterator(const const_iterator&) = default;
		const_iterator(const_iterator&&) = default;

		const_iterator& operator=(const const_iterator&) = default;
		const_iterator& operator=(const_iterator&&) = default;

		~const_iterator() = default;

		// public methods
	public:

		reference operator*() const { return *m_pointer; }
		pointer operator->() const { return m_pointer; }

		const_iterator& operator++()
		{
			m_pointer += m_step;
			return *this;
		}

		const_iterator operator++(int)
		{
			auto temp = *this;
			++*this;
			return temp;
		}

		const_iterator& operator--()
		{
			m_pointer -= m_step;
			return *this;
		}

		const_iterator operator--(int)
		{
			auto temp = *this;
			--*this;
			return temp;
		}

		const_iterator& operator+=(difference_type difference)
		{
			m_pointer += m_step * difference;
			return *this;
		}

		const_iterator operator+(difference_type difference) const
		{
			auto temp = *this;
			temp += difference;
			return temp;
		}

		const_iterator& operator-=(difference_type difference) { return *this += -difference; }

		const_iterator operator-(difference_type difference) const
		{
			auto temp = *this;
			temp -= difference;
			return temp;
		}

		difference_type operator-(const const_iterator& right) const { return (m_pointer - right.m_pointer) / m_step; }

		reference operator[](difference_type difference) const { return *(*this + difference); }

		bool operator==(const const_iterator& right) const { return m_pointer == right.m_pointer; }
		bool operator!=(const const_iterator& right) const { return !(*this == right); }
		bool operator<(const const_iterator& right) const { return m_pointer < right.m_pointer; }
		bool operator>(const const_iterator& right) const { return right < *this; }
		bool operator<=(const const_iterator& right) const { return !(right < *this); }
		bool operator>=(const const_iterator& right) const { return !(*this < right); }

		// private properties
	private:

		const float* m_pointer;
		difference_type m_step;
	};

	inline AudioBufferInterleavedView::ChannelView::const_iterator AudioBufferInterleavedView::ChannelView::cbegin() const
	{
		return { m_ext_buffer, m_step };
	}

	inline AudioBufferInterleavedView::ChannelView::const_iterator AudioBufferInterleavedView::ChannelView::cend() const
	{
		return { m_ext_buffer + size() * m_step, m_step };
	}

	inline AudioBufferInterleavedView::ChannelView::const_iterator AudioBufferInterleavedView::ChannelView::begin() const
	{
		return cbegin();
	}

	inline AudioBufferInterleavedView::ChannelView::const_iterator AudioBufferInterleavedView::ChannelView::end() const
	{
		return cend();
	}
}

#endif
