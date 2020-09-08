///
/// \author Michal Radziszewski <michal.radziszewski@techmo.pl>
/// \date 12.02.2019
///
#ifndef STK__PLAYBACK_PARAMETERS__H
#define STK__PLAYBACK_PARAMETERS__H

#include <cstdint>

namespace stk
{
	/// <summary>
	/// Represents the parameters of a Playback - minimum and maximum boundary of a range to be played
	/// and the repeat count indicating how many times to play it.
	/// </summary>
	class PlaybackParameters
	{
		// public sub-types
	public:

		/// <summary>
		/// Constant used as repeatCount value to indicated that playback should be looped indefinitely.
		/// </summary>
		static constexpr uint32_t Looped = ~static_cast<uint32_t>(0u);

		// public construction and destruction methods
	public:

		/// <summary>
		/// Creates the playback parameters, which are argument of playback creation.
		/// </summary>
		/// <param name="begin">Begin point of the created playback, in [0, 1] range.
		/// Default value 0 means that playback sample is not trimmed at the beginning.</param>
		/// <param name="end">End point of the created playback, in [0, 1] range, must be not less than begin.
		/// Default value 1 means that playback sample is not trimmed at the end.</param>
		/// <param name="repeatCount">Specifies how many times the playback sample is repeated.
		/// The special value Looped means that playback is played in loop,
		/// indefinitely, until manually stopped.</param>
		constexpr PlaybackParameters(float begin = 0.0f, float end = 1.0f, uint32_t repeatCount = 1u):
			m_begin(begin), m_end(end), m_repeatCount(repeatCount) {}

		// public methods
	public:

		/// <summary>
		/// Returns the beginning point of playback.
		/// </summary>
		constexpr float begin() const {return m_begin;}

		/// <summary>
		/// Returns the end point of playback.
		/// </summary>
		constexpr float end() const {return m_end;}

		/// <summary>
		/// Returns the repeat count of playback, or 0 if playback is looped.
		/// </summary>
		constexpr uint32_t repeatCount() const {return m_repeatCount;}

		/// <summary>
		/// Returns true if playback is looped, or false otherwise.
		/// </summary>
		constexpr bool isLooped() const {return m_repeatCount == Looped;}

		/// <summary>
		/// Returns true if playback parameters are valid, false otherwise.
		/// </summary>
		constexpr bool areValid() const {return 0.0f <= m_begin && m_begin <= m_end && m_end <= 1.0f;}

		// private properties
	private:

		float m_begin;
		float m_end;
		uint32_t m_repeatCount;
	};
}

#endif
