///
/// \author Daniel Szetela <daniel.szeteka@techmo.pl>
/// \date 18.03.2019
///
#ifndef STK_EX__UTILITY__MESH_FACE_VALIDATOR__H
#define STK_EX__UTILITY__MESH_FACE_VALIDATOR__H

#include <stk/Math.h>

namespace stk_ex::utility
{
	/// <summary>
	/// Checks whether given face is valid stk triangle.
	/// </summary>
	/// <param name="face">The face to validate.</param>
	/// <returns>True, if provided face is valid stk triangle, false otherwise.</returns>
	bool isValidMeshFace(stk::face face);
}

#endif
