///
/// \author Michal Radziszewski <michal.radziszewski@techmo.pl>
/// \date 20.02.2019
///
#ifndef STK__I_ACOUSTIC_MEDIUM__H
#define STK__I_ACOUSTIC_MEDIUM__H

#include <functional>
#include "IEffect.h"

namespace stk
{
	/// <summary>
	/// Controls the acoustic medium, which affects sound speed and causes sound damping with distance.
	/// </summary>
	class IAcousticMedium
	{
		// public sub-types
	public:

		/// <summary>
		/// A callback called with the obtained speed of sound after speedOfSound() call.
		/// </summary>
		using SpeedOfSoundCallback = std::function<void(float speed)>;

		// public methods
	public:

		/// <summary>
		/// Asynchronously sets the speed of sound in the medium, in m/s.
		/// </summary>
		/// <param name="speed">The speed to set.</param>
		virtual void setSpeedOfSound(float speed) = 0;

		/// <summary>
		/// Obtains the speed of sound in this medium, in m/s.
		/// </summary>
		/// <param name="callback">The callback called with the obtained speed.</param>
		virtual void speedOfSound(SpeedOfSoundCallback callback) = 0;

		/// <summary>
		/// Controls the damping with distance effect on this medium.
		/// </summary>
		virtual IEffect& dampingWithDistance() = 0;

		// protected construction and destruction methods
	protected:
		virtual ~IAcousticMedium() = default;
	};
}

#endif
