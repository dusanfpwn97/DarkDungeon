///
/// \author Marta Kucejko <marta.kucejko@techmo.pl>
/// \date 14.02.2019
///
#ifndef STK_EX__ATTENUATION__PREDEFINED_ATTENUATION_FUNCTIONS__H
#define STK_EX__ATTENUATION__PREDEFINED_ATTENUATION_FUNCTIONS__H

namespace stk_ex::attenuation
{
	/// <summary>
	/// No attenuation over distance (attenuation of a plane wave)
	/// </summary>
	float nothing();

	/// <summary>
	/// Inverse square of distance law (-6dB/doubling the distance) - natural attenuation of a point source.
	/// </summary>
	float pointSource(float distance, float radius);

	/// <summary>
	/// Inverse distance law (-3dB/doubling distance) - attenuation of a line source.
	/// </summary>
	float lineSource(float distance, float radius);

	/// <summary>
	/// Attenuation over distance falls linearly from source radius to maxDistance. Good for sounds that
	/// don't need exact 3D localization like background looped sounds or ambients.
	/// </summary>
	float linear(float distance, float radius, float maxDistance);

	/// <summary>
	/// Logarithmic reduction of volume in distance. Good for sounds that need more precise localization, making sounds
	/// loud at close distance decreasingwith distance.  
	/// </summary>
	float logarithmic(float distance, float radius, float maxDistance);

	/// <summary>
	/// A very steep curve in the shape of a hyperbole, very loud at the close distance with significant decrease over distance.
	/// </summary>
	float inverse(float distance, float radius, float maxDistance);

	/// <summary>
	/// A reverse logarithmic reduction. Useful for sounds that need to be loud up to their maxRadius.
	/// </summary>
	float reverseLog(float distance, float radius, float maxDistance);
}

#endif
