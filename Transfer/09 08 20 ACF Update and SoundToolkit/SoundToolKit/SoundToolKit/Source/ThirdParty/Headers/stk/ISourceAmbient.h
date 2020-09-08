///
/// \author Michal Radziszewski <michal.radziszewski@techmo.pl>
/// \date 19.02.2019
///
#ifndef STK__I_SOURCE_AMBIENT__H
#define STK__I_SOURCE_AMBIENT__H

#include "ISource.h"

namespace stk
{
	/// <summary>
	/// The public ambient sound source interface.
	/// An ambient sound source does not have neither position in space nor attenuation.
	/// Its emitted sound does not interact with scene geometry.
	/// </summary>
	class ISourceAmbient: public virtual ISource
	{
		// protected construction and destruction methods
	protected:
		virtual ~ISourceAmbient() = default;
	};
}

#endif
