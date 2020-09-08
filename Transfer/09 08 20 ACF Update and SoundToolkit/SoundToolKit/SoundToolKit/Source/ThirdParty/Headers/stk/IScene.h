///
/// \author Michal Radziszewski <michal.radziszewski@techmo.pl>
/// \date 14.05.2019
///
#ifndef STK__I_SCENE__H
#define STK__I_SCENE__H

#include <functional>
#include "ArrayView.h"
#include "SharedResource.h"
#include "SpatialEffectType.h"
#include "IModel.h"

namespace stk
{
	class IReceiver;
	class IAcousticMedium;

	/// <summary>
	/// The interface for controlling Receiver, Acoustic Medium, and Models.
	/// </summary>
	class IScene
	{
		// public sub-types
	public:

		/// <summary>
		/// A callback called with a view on obtained scene's models.
		/// </summary>
		/// <param name="models">The obtained view on all scene Models.</param>
		using GetModelsCallback = std::function<void(ArrayView<SharedResource<IModel>> models)>;

		/// <summary>
		/// The callback called with the obtained spatial effect enabled/disabled state.
		/// </summary>
		/// <param name="isEnabled>True if spatial effect is enabled, false otherwise.</param>
		using IsEnabledCallback = std::function<void(bool isEnabled)>;

		// public methods
	public:

		/// <summary>
		/// Obtains the reference for Receiver, which controls a virtual microphone.
		/// </summary>
		/// <returns>The reference for Receiver interface.</returns>
		virtual IReceiver& receiver() = 0;

		/// <summary>
		/// Obtains the reference for AcousticMedium, which controls speed of sound and sound damping with distance.
		/// </summary>
		/// <returns>The reference for AcousticMedium interface.</returns>
		virtual IAcousticMedium& acousticMedium() = 0;

		/// <summary>
		/// Asynchronously adds a model to the scene.
		/// </summary>
		/// <note>Only models added to scene participate in sound processing.</note>
		/// <param name="model">The model to add.</param>
		virtual void addModel(SharedResource<IModel> model) = 0;

		/// <summary>
		/// Asynchronously removes a model from the scene.
		/// </summary>
		/// <note>Only models added to scene participate in sound processing.</note>
		/// <param name="model">The model to remove, or no-op if model is nullptr.</param>
		virtual void removeModel(IModel* model) = 0;

		/// <summary>
		/// Asynchronously calls the provided callback with a view on all scene models.
		/// </summary>
		/// <param name="callback">The callback to be called with a view on scene models.</param>
		virtual void getModels(GetModelsCallback callback) = 0;

		/// <summary>
		/// Asynchronously clears the scene state:
		/// - resets the receiver to default values
		/// - resets the acoustic medium to default values
		/// - removes all models from the scene.
		/// </summary>
		/// <note>The models are not released by this method.</note>
		virtual void clear() = 0;

		/// <summary>
		/// Asynchronously enables the given spatial effect for the entire scene.
		/// </summary>
		/// <param name="effectType">The effect to enable.</param>
		virtual void enableSpatialEffect(SpatialEffectType effectType) = 0;

		/// <summary>
		/// Asynchronously disables the given spatial effect for the entire scene.
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
		/// Synchrnously enables reverberation computation.
		/// </summary>
		virtual void enableReverberation() = 0;

		/// <summary>
		/// Synchronously disables reverberation computation.
		/// </summary>
		virtual void disableReverberation() = 0;

		/// <summary>
		/// Checks if reverberation is enabled.
		/// </summary>
		/// <returns>True if reverberation is enabled, false otherwise.</returns>
		virtual bool isReverberationEnabled() const = 0;

		/// <summary>
		/// Sets ambient-class volume of the whole scene. The STK engine uses hierarchical volume representation,
		/// i.e. master, sound source class, sound source, and playback. The final volume to scale the sound in a
		/// specific playback is affected by multiplication of the volume at all of these four volumes.
		/// </summary>
		/// <param name="volume">The volume to set. Must be a finite, non-negative value.</param>
		virtual void setAmbientVolume(float volume) = 0;

		/// <summary>
		/// Sets spatial-class volume of the whole scene. The STK engine uses hierarchical volume representation,
		/// i.e. master, sound source class, sound source, and playback. The final volume to scale the sound in a
		/// specific playback is affected by multiplication of the volume at all of these four volumes.
		/// </summary>
		/// <param name="volume">The volume to set. Must be a finite, non-negative value.</param>
		virtual void setSpatialVolume(float volume) = 0;

		/// <summary>
		/// Sets reverberation volume of the whole scene. The STK engine uses hierarchical volume representation,
		/// i.e. master, sound source class, sound source, and playback. The final volume to scale the sound in a
		/// specific playback is affected by multiplication of the volume at all of these four volumes.
		/// </summary>
		/// <param name="volume">The volume to set. Must be a finite, non-negative value.</param>
		virtual void setReverbVolume(float volume) = 0;

		/// <summary>
		/// Gets the volume scale of all ambient sound sources.
		/// </summary>
		/// <returns>The current volume of all ambient sound sources.</returns>
		virtual float ambientVolume() const = 0;

		/// <summary>
		/// Gets the volume scale of all spatial sound sources.
		/// </summary>
		/// <returns>The current volume of all spatial sound sources.</returns>
		virtual float spatialVolume() const = 0;

		/// <summary>
		/// Gets the volume scale of reverberation effect.
		/// </summary>
		/// <returns>The current volume of reverberation effect.</returns>
		virtual float reverbVolume() const = 0;

		// protected construction and destruction methods
	protected:
		virtual ~IScene() = default;
	};
}

#endif
