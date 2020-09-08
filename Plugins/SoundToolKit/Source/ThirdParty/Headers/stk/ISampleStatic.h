///
/// \author Michal Radziszewski <michal.radziszewski@techmo.pl>
/// \date 25.11.2018
///
#ifndef STK__I_SAMPLE_STATIC__H
#define STK__I_SAMPLE_STATIC__H

#include "stk/ISample.h"

namespace stk
{
	/// <summary>
	/// Interface for static samples
	/// </summary>
	class ISampleStatic: public virtual ISample
	{
		// public methods
	public:

		// protected construction and destruction methods
	protected:
		~ISampleStatic() = default;
	};
}

#endif
