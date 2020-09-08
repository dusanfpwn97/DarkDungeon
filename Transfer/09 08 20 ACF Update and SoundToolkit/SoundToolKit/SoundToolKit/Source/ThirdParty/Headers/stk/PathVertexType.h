///
/// \author Michal Radziszewski <michal.radziszewski@techmo.pl>
/// \date 06.05.2019
///
#ifndef STK__PATH_VERTEX_TYPE__H
#define STK__PATH_VERTEX_TYPE__H

namespace stk
{
	/// <summary>
	/// The type of a vertex of a sound path - source, receiver, or one of the supported effects.
	/// Source is always the first vertex of the path, and Receiver is always the last one.
	/// In between, there is zero or more effects like reflection or diffraction.
	/// </summary>
	enum class PathVertexType: int
	{
		Source = 0,
		Receiver = 1,
		Reflection = 2,
		Scattering = 3,
		Transmission = 4,
		Diffraction = 5
	};
}

#endif
