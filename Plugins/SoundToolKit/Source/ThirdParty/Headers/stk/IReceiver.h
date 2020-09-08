///
/// \author Michal Radziszewski <michal.radziszewski@techmo.pl>
/// \date 21.02.2019
///
#ifndef STK__I_RECEIVER__H
#define STK__I_RECEIVER__H

#include <functional>
#include "ITransformable.h"

namespace stk
{
	/// <summary>
	/// Controls the receiver (a virtual microphone), its position, orientation, etc.
	/// </summary>
	class IReceiver: public virtual ITransformable
	{
		// public methods
	public:

		/// <summary>
		/// Synchronously enables the Doppler effect computations to account for receiver velocity.
		/// </summary>
		virtual void enableDopplerEffect() = 0;

		/// <summary>
		/// Synchronously disables the Doppler effect computations to account for receiver velocity.
		/// </summary>
		virtual void disableDopplerEffect() = 0;

		/// <summary>
		/// Checks if the Doppler effect on receiver is enabled.
		/// </summary>
		/// <returns>True if the Doppler effect is enabled for the receiver, false otherwise.</returns>
		virtual bool isDopplerEffectEnabled() const = 0;

		// protected construction and destruction methods
	protected:

		virtual ~IReceiver() = default;
	};
}

#endif
