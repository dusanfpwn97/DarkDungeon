///
/// \author Michal Radziszewski <michal.radziszewski@techmo.pl>
/// \date 14.03.2019
///
#ifndef STK__I_SOURCE_SPATIAL__H
#define STK__I_SOURCE_SPATIAL__H

#include <functional>
#include "SharedResource.h"
#include "SpatialEffectType.h"
#include "ISource.h"
#include "ITransformable.h"

namespace stk
{
	class IDirectivity;
	class IMesh;

	/// <summary>
	/// The public spatial sound source interface.
	/// A spatial sound source is placed at requested position in the scene, and its emitted sound interacts
	/// with the scene geometry. The spatial sources support sound attenuation as well.
	/// </summary>
	class ISourceSpatial : public virtual ISource, public virtual ITransformable
	{
		// public sub-types
	public:

		/// <summary>
		/// The sound attenuation as a function of distance - attenuation effect multiplies sound on sound paths
		/// by attenuation factor - a returned value. The value should be in [0, 1] range, where 1 means no attenuation
		/// (full sound intensity), and 0 means full attenuation (no sound at all).
		/// </summary>
		/// <param name="distance">The distance from sound source, measured along a sound path, in metres.</param>
		using AttenuationFunction = std::function<float(float distance)>;

		/// <summary>
		/// The callback called with the obtained directivity model used by this source,
		/// or null pointer if the source is non-directional.
		/// </summary>
		/// <param name="directivity">The obtained directivity model.</param>
		using DirectivityCallback = std::function<void(SharedResource<IDirectivity> directivity)>;

		/// <summary>
		/// The callback called with the obtained sound emitting surface,
		/// or null pointer if the source is a spherical source.
		/// </summary>
		/// <param name="surface">The obtained sound emitting surface.</summary>
		using SurfaceCallback = std::function<void(SharedResource<IMesh> surface)>;

		/// <summary>
		/// The callback called with the copy of set custom attenuation function,
		/// or null function if the source uses default attenuation.
		/// </summary>
		/// <param name="function">The obtained copy of attenuation function.</summary>
		using AttenuationFunctionCallback = std::function<void(AttenuationFunction function)>;

		/// <summary>
		/// The callback called with the obtained simulation quality of the source.
		/// </summary>
		/// <param name="quality>The obtained simulation quality.</param>
		using SimulationQualityCallback = std::function<void(float quality)>;

		/// <summary>
		/// The callback called with the obtained spatial effect enabled/disabled state.
		/// </summary>
		/// <param name="isEnabled>True if spatial effect is enabled, false otherwise.</param>
		using IsEnabledCallback = std::function<void(bool isEnabled)>;

		// public methods
	public:

		/// <summary>
		/// Asynchronously sets the directivity model to use by this source.
		/// Providing null pointer makes the source non-directional (which is default).
		/// </summary>
		/// <param name="directivity">The directivity model to set or null pointer to remove directivity.</param>
		virtual void setDirectivity(SharedResource<IDirectivity> directivity) = 0;

		/// <summary>
		/// Asynchronously calls the provided callback with the obtained directivity model.
		/// </summary>
		/// <param name="callback">The callback to be called with the obtained directivity model.</param>
		virtual void directivity(DirectivityCallback callback) = 0;

		/// <summary>
		/// Asynchronously sets the arbitrarily shaped surface which emits the sound.
		/// Providing null pointer makes the source spherical (which is default).
		/// </summary>
		/// <param name="surface">The mesh which defines the sound emitting surface.</param>
		virtual void setSourceSurface(SharedResource<IMesh> surface) = 0;

		/// <summary>
		/// Asynchronously calls the provided callback with the obtained sound emitting surface.
		/// </summary>
		/// <param name="callback">The callback to be called with the obtained sound emitting surface.</param>
		virtual void sourceSurface(SurfaceCallback callback) = 0;

		/// <summary>
		/// Asynchronously sets the copy of the provided attenuation function.
		/// Providing null function reverts to default attenuation (1/distance^2).
		/// </summary>
		/// <param name="function">The attenuation function to attenuate sound on paths from this source.</param>
		virtual void setAttenuation(AttenuationFunction function) = 0;

		/// <summary>
		/// Asynchronously calls the provided callback with the obtained copy of the attenuation function.
		/// </summary>
		/// <param name="callback">The callback to be called with the obtained copy of the attenuation function.</param>
		virtual void attenuation(AttenuationFunctionCallback callback) = 0;

		/// <summary>
		/// Asynchronously sets the relative quality of source processing. The sources with higher desired simulation
		/// quality receive more engine resources for processing them, and are less likely to be entirely skipped.
		/// </summary>
		/// <param name="quality">Simulation quality in range [0, 1], where 1 (default) is the best quality.</param>
		virtual void setSimulationQuality(float quality) = 0;

		/// <summary>
		/// Asynchronously calls the provided callback with the obtained source processing quality.
		/// </summary>
		/// <param name="callback">The callback to be called with the obtained simulation quality.</param>
		virtual void simulationQuality(SimulationQualityCallback callback) = 0;

		/// <summary>
		/// Asynchronously enables the given spatial effect for this source.
		/// </summary>
		/// <param name="effectType">The effect to enable.</param>
		virtual void enableSpatialEffect(SpatialEffectType effectType) = 0;

		/// <summary>
		/// Asynchronously disables the given spatial effect for this source.
		/// </summary>
		/// <param name="effectType">The effect to disable.</param>
		virtual void disableSpatialEffect(SpatialEffectType effectType) = 0;

		/// <summary>
		/// Checks if the given spatial effect is enabled.
		/// </summary>
		/// <param name="effectType">The effect to check.</param>
		/// <param name="callback">A callback called with true if the effect is enabled, with false otherwise.</param>
		virtual void isSpatialEffectEnabled(SpatialEffectType effectType, IsEnabledCallback callback) = 0;

		/// <summary>
		/// Synchronously enables the doppler effect computations accounting for velocity of this sound source.
		/// </summary>
		virtual void enableDopplerEffect() = 0;

		/// <summary>
		/// Synchronously disables the doppler effect computations accounting for velocity of this sound source.
		/// </summary>
		virtual void disableDopplerEffect() = 0;

		/// <summary>
		/// Checks if Doppler effect simulation is enabled for this source.
		/// </summary>
		/// <returns>True if the Doppler effect is enabled for this source, false otherwise.</returns>
		virtual bool isDopplerEffectEnabled() const = 0;

		/// <summary>
		/// Synchronously enables HRTF spatialization for this sound source.
		/// </summary>
		/// <note>The HRTF spatialization is used when audio output is set to headphones,
		/// and HRTF data is provided, and global HRTF setting is enabled.</note>
		virtual void enableHrtfSpatialization() = 0;

		/// <summary>
		/// Synchronously disables HRTF spatialization for this sound source.
		/// </summary>
		virtual void disableHrtfSpatialization() = 0;

		/// <summary>
		/// Checks if HRTF spatialization is enabled for this source.
		/// </summary>
		/// <returns>True if HRTF spatialization is enabled for this sound source, false otherwise.</returns>
		virtual bool isHrtfSpatializationEnabled() const = 0;

		/// <summary>
		/// Synchronously enables reverberation for sound emitted by this source.
		/// </summary>
		virtual void enableReverberation() = 0;

		/// <summary>
		/// Synchronously disables reverberation for sound emitted by this source.
		/// </summary>
		virtual void disableReverberation() = 0;

		/// <summary>
		/// Checks if reverberation is enabled for this source.
		/// </summary>
		/// <returns>True if reverberation is enabled for this sound source, false otherwise.</returns>
		virtual bool isReverberationEnabled() const = 0;

		// protected construction and destruction methods
	protected:
		virtual ~ISourceSpatial() = default;
	};
}

#endif
