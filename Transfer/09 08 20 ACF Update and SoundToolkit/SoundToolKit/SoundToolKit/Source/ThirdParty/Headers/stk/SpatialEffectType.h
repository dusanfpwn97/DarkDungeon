///
/// \author Michal Radziszewski <michal.radziszewski@techmo.pl>
/// \date 06.05.2019
///
#ifndef STK__SPATIAL_EFFECT_TYPE__H
#define STK__SPATIAL_EFFECT_TYPE__H

namespace stk
{
	/// <summary>
	/// Spatial effects are effects which affect sound paths generation.
	/// These effects are controlled by per-scene and per source basis.
	/// Any such effect is considered to be enabled for sound emitted by
	/// a source if it is enabled for both the source and the scene.
	/// These effects are enabled, disabled, and queried asynchronously.
	/// By default, all these effects are enabled.
	/// </summary>
	enum class SpatialEffectType: int
	{
		/// <summary>
		/// Attenuation of sound with distance.
		/// </summary>
		Attenuation = (1 << 0),

		/// <summary>
		/// Specular reflection of sound from geometric obstacles.
		/// </summary>
		Reflection = (1 << 1),

		/// <summary>
		/// Sound scattering (diffuse reflection) on geometric obstacles.
		/// </summary>
		Scattering = (1 << 2),

		/// <summary>
		/// Sound transmission through geometric obstacles.
		/// </summary>
		Transmission = (1 << 3),

		/// <summary>
		/// Diffraction of acoustic waves on edges of geometric obstacles.
		/// </summary>
		Diffraction = (1 << 4)
	};
}

#endif
