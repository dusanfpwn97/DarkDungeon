///
/// \author Michal Radziszewski <michal.radziszewski@techmo.pl>
/// \date 25.11.2018
///
#ifndef STK__I_SAMPLE__H
#define STK__I_SAMPLE__H

#include <cstddef>
#include "IResource.h"

namespace stk
{
	/// <summary>
	/// Common base class for both Static and Streaming Sample Sources.
	/// </summary>
	class ISample: public virtual IResource
	{
		// public methods
	public:
		/// <returns>
		/// The number of channels in the enclosed raw samples data.
		/// </returns>
		virtual size_t numberOfChannels() const = 0;

		// protected construction and destruction methods
	protected:
		virtual ~ISample() = default;
	};
}

#endif
