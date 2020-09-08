///
/// \author Daniel Szetela <daniel.szetela@techmo.pl>
/// \date 28.02.2019
///
#ifndef STK__I_SOURCE_AMBIENT_SEPARATELY_OUTPUT__H
#define STK__I_SOURCE_AMBIENT_SEPARATELY_OUTPUT__H

#include "ISourceAmbient.h"

namespace stk
{
	/// <summary>
	/// The public separately output ambient sound source interface.
	/// Audio output for this kind of ambient sound source is not mixed with other
	/// sources on the scene but rendered separately.
	/// <summary>
	class ISourceAmbientSeparatelyOutput : public virtual ISourceAmbient
	{
		// protected construction and destruction methods
	protected:
		~ISourceAmbientSeparatelyOutput() = default;
	};
}

#endif
