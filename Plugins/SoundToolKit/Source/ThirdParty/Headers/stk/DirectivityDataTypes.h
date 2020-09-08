///
/// \author Bartosz Nowacki <bartosz.nowacki@techmo.pl>
/// \date 10.02.2018
///
#ifndef STK__DIRECTIVITY_DATA_TYPES__H
#define STK__DIRECTIVITY_DATA_TYPES__H

#include <array>
#include "stk/IEffect.h"

namespace stk
{
	/// <summary>
	/// Description of symmetry configurations:
	///
	/// ROTATIONAL_1_AXIS - requires provision of points (spline) on half of X-Z plane (positive values of X)
	///						The shape will be revolved around Z axis, providing 3D shape of directivity characteristics.
	///
	/// ROTATIONAL_1_AXIS_FLIP - requires provision of points (spline) on a positive quarter of X-Z plane. The shape will be flipped over
	///							 X axis (negative Z) and revolved around Z axis.
	///
	/// PLANAR_1_PLANE - requires provision of points on half of sphere (positive y values). The solid sphere will be mirrored and mapped to negative y values
	///                  - flipped over X-Z plane. 
	/// 
	/// PLANAR_2_PLANES - requires provision of points in between X-Z and X-Y planes. Points defining surface shape will be mirrored and mapped 
	///                   to three other halfs of coordinate system.
	///
	/// PLANAR_3_PLANES - the same as above, but points are required to be defined only for positive values of all three axes. Then this segment will be mapped 
	///                   and flipped over all three planes of symmetry.
	///
	/// NO_SYMMETRY - no symmetry of data. Uniformly distributed points defining surface shape has to be provided for all directions. 
	/// </summary>
	enum class DirectivitySymmetry
	{
		ROTATIONAL_1_AXIS, // 
		ROTATIONAL_1_AXIS_FLIP, //
		PLANAR_1_PLANE,    //
		PLANAR_2_PLANES,   //
		PLANAR_3_PLANES,   //
		NO_SYMMETRY        //
	};

	using DirectivityData = IEffect::FrequencyInfo;
}

#endif
