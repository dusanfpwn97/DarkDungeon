///
/// \author Daniel Szetela <daniel.szetela@techmo.pl>
/// \date 28.02.2019
///
#ifndef STK__I_SOURCE_SPATIAL_SEPARATELY_OUTPUT__H
#define STK__I_SOURCE_SPATIAL_SEPARATELY_OUTPUT__H

#include "ISourceSpatial.h"

namespace stk
{
	/// <summary>
	/// The public separately output spatial sound source interface.
	/// Audio output for this kind of spatial sound source is not mixed with other
	/// sources on the scene but rendered separately.
	/// <summary>
	class ISourceSpatialSeparatelyOutput : public ISourceSpatial
	{
		// protected construction and destruction methods
	protected:
		~ISourceSpatialSeparatelyOutput() = default;
	};
}

#endif
