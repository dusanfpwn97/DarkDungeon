///
/// \author Michal Radziszewski <michal.radziszewski@techmo.pl>
/// \date 08.12.2018
///
#ifndef STK__I_MATERIAL__H
#define STK__I_MATERIAL__H

#include "IResource.h"
#include "IEffect.h"

namespace stk
{
	/// <summary>
	/// Allows to control acoustic materials.
	/// </summary>
	class IMaterial: public virtual IResource
	{
		// public methods
	public:

		/// <summary>
		/// Controls the absorption effect on this material.
		/// </summary>
		virtual IEffect& absorption() = 0;

		/// <summary>
		/// Controls the scattering effect on this material.
		/// </summary>
		virtual IEffect& scattering() = 0;

		/// <summary>
		/// Controls the transmission effect on this material.
		/// </summary>
		virtual IEffect& transmission() = 0;

		// protected construction and destruction methods
	protected:
		virtual ~IMaterial() = default;
	};
}

#endif
