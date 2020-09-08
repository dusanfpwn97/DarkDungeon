///
/// \author Michal Radziszewski <michal.radziszewski@techmo.pl>
/// \date 16.05.2019
///
#ifndef STK_EX__SCENE__I_SCENE_DESCRIPTION__H
#define STK_EX__SCENE__I_SCENE_DESCRIPTION__H

#include <stk/UniqueResource.h>
#include <stk/SharedResource.h>
#include <stk/StringView.h>
#include <stk/Math.h>
#include <stk/PlaybackParameters.h>
#include <stk/IEffect.h>
#include "stk_ex/scene/Color.h"

namespace stk
{
	class ISoundToolKit;
}

namespace stk_ex::scene
{
	/// <summary>
	/// Defines the scene description to serialize the scene to a text string in json format, which is accepted
	/// by the SceneLoader. The SceneDescription uses a builder pattern to create data structures to serialize.
	/// </summary>
	class ISceneDescription
	{
		// public sub-types
	public:

		/// <summary>
		/// The data necessary to define the scene configuration.
		/// </summary>
		struct ConfigurationData
		{
			uint32_t spatialEffectsMask{ ~0u };
			float ambientVolume{ 1.0f };
			float spatialVolume{ 1.0f };
			float reverbVolume{ 1.0f };
		};

		/// <summary>
		/// The data necessary to define the transformation of a model, a spatial sound source, or a receiver.
		/// </summary>
		struct TransformData
		{
			stk::vec3 position;
			stk::quaternion rotation;
			stk::vec3 linearVelocity;
			stk::vec3 angularVelocity;
		};

		/// <summary>
		/// The data necessary to define all paramters specific to spatial sound sources.
		/// </summary>
		struct SourceSpatialData
		{
#ifdef __clang__
			// workaround for screwed default construction generation in clang
			SourceSpatialData() {}
			SourceSpatialData(stk::StringView d, stk::StringView m, stk::StringView a, float s, uint32_t sem, bool de, bool he, bool re):
				directivityName(d), meshName(m), attenuation(a), simulationQuality(s),
				spatialEffectsMask(sem), dopplerEffectEnabled(de), hrtfSpatializationEnabled(he), reverberationEnabled(re) {}
#endif
			stk::StringView directivityName; // TODO serialized, but unused yet, see issue #509
			stk::StringView meshName;
			stk::StringView attenuation;
			float simulationQuality{ 1.0f };
			uint32_t spatialEffectsMask{ ~0u };
			bool dopplerEffectEnabled{ false };
			bool hrtfSpatializationEnabled{ false };
			bool reverberationEnabled{ true };
		};

		/// <summary>
		/// A handle of a playlist description, which can be used to add playlist items.
		/// </summary>
		using PlaylistHandle = struct TagPlaylist*;

		/// <summary>
		/// A handle of a source description, which can be used to add playbacks.
		/// </summary>
		using SourceHandle = struct TagSource*;

		// public construction and destruction methods
	public:

		/// <summary>
		/// Creates the scene serializer.
		/// </summary>
		/// <param name="stk">The main Sound Tool Kit interface used to manage memory.</param>
		static stk::UniqueResource<ISceneDescription> create(stk::SharedResource<stk::ISoundToolKit> stk);

		// public methods
	public:

		/// <summary>
		/// Releases the scene serializer.
		/// </summary>
		virtual void release() = 0;

		/// <summary>
		/// Overrides the default scene configuration with the requested one.
		/// The method can be called once only, all subsequent calls are ignored.
		/// </summary>
		/// <param name="configuration">The requested scene configuration.</param>
		virtual void setConfiguration(const ConfigurationData& configuration) = 0;

		/// <summary>
		/// Adds a scene-specific setting.
		/// </summary>
		/// <param name="name">The name of the setting.</param>
		/// <param name="value">The value of the setting.</param>
		virtual void addSetting(stk::StringView name, stk::StringView value) = 0;

		/// <summary>
		/// Adds a link between animation curve name and its definition file to the scene description.
		/// </summary>
		/// <param name="name">The name of the animation curve.</param>
		/// <param name="filePath">The relative path to the file containing the animation curve definition.</param>
		virtual void addAnimationCurve(stk::StringView name, stk::StringView filePath) = 0;

		/// <summary>
		/// Switches the animation equalization on for this scene (the default is off).
		/// </summary>
		virtual void enableAnimationsEqualization() = 0;

		/// <summary>
		/// Adds a link between material name and its definition file to the scene description.
		/// </summary>
		/// <param name="name">The name of the material.</param>
		/// <param name="filePath">The relative path to the file containing the material definition.</param>
		virtual void addMaterial(stk::StringView name, stk::StringView filePath) = 0;

		/// <summary>
		/// Adds a link between model name and its definition, as well as other optional model parameters to the scene description.
		/// </summary>
		/// <param name="name">The name of the model.</param>
		/// <param name="filePath">The relative path to the file containing the model definition.</param>
		/// <param name="transformData">The optional transform of the model.</param>
		/// <param name="animationCurve">The optional name of the model's animation curve.</param>
		/// <param name="animationEnabled">The optional enabling/disabling animation for this model.</param>
		/// <note>Using animationEnabled it is possible to disable using animation for this model,
		/// even if the model has an animation curve attached.</note>
		virtual void addModel(stk::StringView name, stk::StringView filePath,
			const TransformData& transformData = TransformData{},
			stk::StringView animationCurve = stk::StringView{},
			bool animationEnabled = true) = 0;

		/// <summary>
		/// Adds a link between static sample name and the file with audio data to the scene description.
		/// </summary>
		/// <param name="name">The name of the sample.</param>
		/// <param name="filePath">The relative path to the file containing the audio data for the sample.</param>
		virtual void addSampleStatic(stk::StringView name, stk::StringView filePath) = 0;

		/// <summary>
		/// Adds a playlist description to the scene description.
		/// </summary>
		/// <param name="name">The name of the playlist.</param>
		/// <returns>A handle of the playlist description, which can be used to add playlist items.</returns>
		virtual PlaylistHandle addPlaylist(stk::StringView name) = 0;

		/// <summary>
		/// Adds a sample to the playlist description.
		/// </summary>
		/// <param name="playlist">The playlist description to add the item to.</param>
		/// <param name="sampleName">The name of the sample to add to the playlist description.</param>
		/// <param name="parameters">The parameters of playlist item - trimming and repeat count.</param>
		virtual void addPlaylistItemSample(PlaylistHandle playlist, stk::StringView sampleName,
			const stk::PlaybackParameters& parameters = stk::PlaybackParameters{}) = 0;

		/// <summary>
		/// Adds an other playlist to the playlist description.
		/// </summary>
		/// <param name="playlist">The playlist description to add the item to.</param>
		/// <param name="playlistName">The name of the playlist to add to the playlist description.</param>
		/// <param name="parameters">The parameters of playlist item - trimming and repeat count.</param>
		/// <note>Creating looped dependency between playlists causes udefined behaviour during scene loading.</note>
		virtual void addPlaylistItemPlaylist(PlaylistHandle playlist, stk::StringView playlistName,
			const stk::PlaybackParameters& parameters = stk::PlaybackParameters{}) = 0;

		// addDirectivity TODO issue #509 implement directivity

		/// <summary>
		/// Adds description of ambient sound source to the scene.
		/// </summary>
		/// <param name="volume">The optional volume of the source.</param>
		/// <returns>A handle of the source description, which can be used to add playbacks.</returns>
		virtual SourceHandle addSourceAmbient(stk::StringView name, float volume = 1.0f) = 0;

		/// <summary>
		/// Adds description of spatial sound source to the scene.
		/// </summary>
		/// <param name="volume">The optional volume of the source.</param>
		/// <param name="transformData">The optional transform of the source.</param>
		/// <param name="sourceData">The optional extra parameters of the spatial source.</param>
		/// <returns>A handle of the source description, which can be used to add playbacks.</returns>
		virtual SourceHandle addSourceSpatial(stk::StringView name,
			float volume = 1.0f,
			const TransformData& transformData = TransformData{},
			const SourceSpatialData& sourceData = SourceSpatialData{}) = 0;

		/// <summary>
		/// Adds a link between playback name, and a sample name with source handle used to play sound.
		/// </summary>
		/// <param name="playbackName">The name of the playback.</param>
		/// <param name="sampleName">The name of the sample with sound data.</param>
		/// <param name="source">The handle of the source which would be used to emit the sound.</param>
		/// <param name="volume">The volume of the playback.</param>
		/// <param name="parameters">The parameters of playback - trimming, repeat count, and looped.</param>
		virtual void addPlaybackWithSample(stk::StringView playbackName, stk::StringView sampleName, SourceHandle source,
			float volume = 1.0f, const stk::PlaybackParameters& parameters = stk::PlaybackParameters{}) = 0;

		/// <summary>
		/// Adds a link between playback name, and a playlist name with source handle used to play sound.
		/// </summary>
		/// <param name="playbackName">The name of the playback.</param>
		/// <param name="playlistName">The name of the playlist with samples or other playlists.</param>
		/// <param name="source">The handle of the source which would be used to emit the sound.</param>
		/// <param name="volume">The volume of the playback.</param>
		/// <param name="parameters">The parameters of playback - trimming, repeat count, and looped.</param>
		virtual void addPlaybackWithPlaylist(stk::StringView playbackName, stk::StringView playlistName, SourceHandle source,
			float volume = 1.0f, const stk::PlaybackParameters& parameters = stk::PlaybackParameters{}) = 0;

		/// <summary>
		/// Overrides the default speed of sound in the acoustic medium by the requested value.
		/// The method can be called once only, all subsequent calls are ignored.
		/// </summary>
		/// <param name="speed">The speed of sound to set.</param>
		virtual void setSpeedOfSound(float speed) = 0;

		/// <summary>
		/// Overrides the default sound damping coefficients with the requested ones.
		/// The method can be called once only, all subsequent calls are ignored.
		/// </summary>
		/// <param name="coefficients">The requested coefficients.</param>
		virtual void setMediumDampingCoefficients(const stk::IEffect::Coefficients& coefficients) = 0;

		/// <summary>
		/// Enables the sound damping with distance effect in acoustic medium (the default is disabled).
		/// </summary>
		virtual void enableMediumDamping() = 0;

		/// <summary>
		/// Overrides the default receiver transform (zero position, no rotation, zero velocity) with the requested one.
		/// The method can be called once only, all subsequent calls are ignored.
		/// </summary>
		/// <param name="transformData">The requested receiver transform.</param>
		virtual void setReceiverTransform(const TransformData& transformData) = 0;

		/// <summary>
		/// Switches the simulation of the Doppler effect on for receiver on this scene (the default is off).
		/// </summary>
		virtual void enableReceiverDopplerEffect() = 0;

		/// <summary>
		/// Sets the animation curve name for the receiver (the default is no animation, i.e. null or empty view).
		/// The method can be called once only, all subsequent calls are ignored.
		/// </summary>
		/// <param name="animationCurve">The name of the animation curve.</param>
		virtual void setReceiverAnimation(stk::StringView animationCurve) = 0;

		/// <summary>
		/// Disables the animation for the receiver (the default is enabled).
		/// </summary>
		/// <note>Using this method it is possible to disable using animation for receiver,
		/// even if the receiver has an animation curve attached.</note>
		virtual void disableReceiverAnimation() = 0;

		/// <summary>
		/// Adds visual-only information to the given mesh of the given model.
		/// </summary>
		/// <param name="modelName">The name of the model which owns the mesh.</param>
		/// <param name="meshName">The name of the mesh, which is unique across the model only.</param>
		/// <param name="color">Optional color to be used to display this mesh (the default is implementation defined).</param>
		/// <param name="visible">Optional information if mesh should be visible (the default is true).</param>
		virtual void addMeshVisual(stk::StringView modelName, stk::StringView meshName, const Color* color, bool visible = true) = 0;

		// protected construction and destruction methods
	protected:

		virtual ~ISceneDescription() = default;
	};
}

#endif
