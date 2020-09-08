///
/// \author Michal Radziszewski <michal.radziszewski@techmo.pl>
/// \date 15.05.2019
///
#ifndef STK_EX__SCENE__SCENE_LOADER__H
#define STK_EX__SCENE__SCENE_LOADER__H

#include <functional>
#include <stk/StringView.h>
#include <stk/SharedResource.h>
#include "Color.h"

namespace stk
{
	class ISoundToolKit;
	class IMaterial;
	class IMesh;
	class IModel;
	class ISampleStatic;
	class IPlaylist;
	class IDirectivity;
	class ISourceAmbient;
	class ISourceSpatial;
	class IPlayback;
}

namespace stk_ex::scene
{
	/// <summary>
	/// A callback called for each setting value loaded within the scene.
	/// </summary>
	/// <param name="name">The name of the setting.</param>
	/// <param name="name">The value of the setting.</param>
	using SettingCallback = std::function<void(stk::StringView name, stk::StringView value)>;

	/// <summary>
	/// A callback called for each material loaded within the scene.
	/// </summary>
	/// <param name="name">The name of the material.</param>
	/// <param name="filePath">The relative path to the file containing the material definition.</param>
	/// <param name="material">The created material.</param>
	using MaterialCallback = std::function<void(stk::StringView name, stk::StringView filePath, stk::SharedResource<stk::IMaterial> material)>;

	/// <summary>
	/// A callback called for each mesh loaded within the scene.
	/// </summary>
	/// <param name="name">The name of the mesh.</param>
	/// <param name="mesh">The created mesh.</param>
	using MeshCallback = std::function<void(stk::StringView name, stk::SharedResource<stk::IMesh> mesh)>;

	/// <summary>
	/// A callback called for each model loaded within the scene.
	/// </summary>
	/// <param name="name">The name of the model.</param>
	/// <param name="filePath">The relative path to the file containing the meshes to create the model.</param>
	/// <param name="model">The created model.</param>
	using ModelCallback = std::function<void(stk::StringView name, stk::StringView filePath, stk::SharedResource<stk::IModel> model)>;

	/// <summary>
	/// A callback called for each static sample loaded within the scene.
	/// </summary>
	/// <param name="name">The name of the sample.</param>
	/// <param name="filePath">The relative path to the file containing the audio data to create the sample.</param>
	/// <param name="sample">The created sample.</param>
	using SampleStaticCallback = std::function<void(stk::StringView name, stk::StringView filePath, stk::SharedResource<stk::ISampleStatic> sample)>;

	/// <summary>
	/// A callback called for each playlist loaded within the scene.
	/// </summary>
	/// <param name="name">The name of the playlist.</param>
	/// <param name="playlist">The created playlist.</param>
	using PlaylistCallback = std::function<void(stk::StringView name, stk::SharedResource<stk::IPlaylist> playlist)>;

	/// <summary>
	/// A callback called for each directivity model loaded within the scene.
	/// </summary>
	/// <param name="name">The name of the directivity model.</param>
	/// <param name="filePath">The relative path to the file containing the directivity data to create the model.</param>
	/// <param name="directivity">The created directivity model.</param>
	using DirectivityCallback = std::function<void(stk::StringView name, stk::StringView filePath, stk::SharedResource<stk::IDirectivity> directivity)>;

	/// <summary>
	/// A callback called for each ambient sound source loaded within the scene.
	/// </summary>
	/// <param name="name">The name of the sound source.</param>
	/// <param name="source">The created sound source.</param>
	using SourceAmbientCallback = std::function<void(stk::StringView name, stk::SharedResource<stk::ISourceAmbient> source)>;

	/// <summary>
	/// A callback called for each spatial sound source loaded within the scene.
	/// </summary>
	/// <param name="name">The name of the sound source.</param>
	/// <param name="source">The created sound source.</param>
	using SourceSpatialCallback = std::function<void(stk::StringView name, stk::SharedResource<stk::ISourceSpatial> source)>;

	/// <summary>
	/// A callback called for each playback loaded within the scene.
	/// </summary>
	/// <param name="name">The name of the playback.</param>
	/// <param name="playback">The created playback.</param>
	using PlaybackCallback = std::function<void(stk::StringView name, stk::SharedResource<stk::IPlayback> playback)>;

	/// <summary>
	/// A callback called with requested attenuation function name.
	/// </summary>
	/// <param name="source">The spatial sound source for which the attenuation should be set.</param>
	/// <param name="attenuationFunctionName">The name of the attenuation function to set.</param>
	using AttenuationCallback = std::function<void(stk::SharedResource<stk::ISourceSpatial> source, stk::StringView attenuationFunctionName)>;

	/// <summary>
	/// A callback called for each animation curve which is defined in the scene.
	/// </summary>
	/// <param name="name">The name of the animation curve.</param>
	/// <param name="filePath">The relative path to the file containing the animation data.</param>
	using AnimationCurveCallback = std::function<void(stk::StringView name, stk::StringView filePath)>;

	/// <summary>
	/// A callback called for each model animation.
	/// </summary>
	/// <param name="modelName">The model to attach the animation to.</param>
	/// <param name="animationName">The name of the animation curve to be attached.</param>
	/// <param name="enabled">True if the animation should be enabled by default, false otherwise.</param>
	using ModelAnimationCallback = std::function<void(stk::SharedResource<stk::IModel> model, stk::StringView animationName, bool enabled)>;

	/// <summary>
	/// A callback called for each sound source animation.
	/// </summary>
	/// <param name="source">The sound source to attach the animation to.</param>
	/// <param name="animationName">The name of the animation curve to be attached.</param>
	/// <param name="enabled">True if the animation should be enabled by default, false otherwise.</param>
	using SourceAnimationCallback = std::function<void(stk::SharedResource<stk::ISourceSpatial> source, stk::StringView animationName, bool enabled)>;

	/// <summary>
	/// A callback called for the receiver animation.
	/// </summary>
	/// <param name="animationName">The name of the animation curve to be attached.</param>
	/// <param name="enabled">True if the animation should be enabled by default, false otherwise.</param>
	using ReceiverAnimationCallback = std::function<void(stk::StringView animationName, bool enabled)>;

	/// <summary>
	/// A callback called once for scene with animation equalization enable/disable status.
	/// </summary>
	/// <param name="enabled">True if all animations should be equalized, false otherwise.</param>
	using AnimationsEqualizeCallback = std::function<void(bool enabled)>;

	/// <summary>
	/// A callback called for each mesh visual information.
	/// </summary>
	/// <param name="modelName">Name of model for which the mesh belongs.</param>
	/// <param name="meshName">Name of mesh, which is unique inside the model.</param>
	/// <param name="color">Optional suggested mesh display color, or nullptr if no color information is given.</param>
	/// <param name="visible">True if mesh should be visible in renderer, false otherwise.</param>
	using MeshVisualCallback = std::function<void(stk::StringView modelName, stk::StringView meshName, const Color* color, bool visible)>;

	/// <summary>
	/// Callbacks called during loading of scene for each created STK resource.
	/// </summary>
	struct SceneLoaderCallbacks
	{
		SettingCallback m_settingCallback;
		MaterialCallback m_materialCallback;
		MeshCallback m_meshCallback;
		ModelCallback m_modelCallback;
		SampleStaticCallback m_sampleStaticCallback;
		PlaylistCallback m_playlistCallback;
		DirectivityCallback m_directivityCallback;
		SourceAmbientCallback m_sourceAmbientCallback;
		SourceSpatialCallback m_sourceSpatialCallback;
		PlaybackCallback m_playbackCallback;
		AttenuationCallback m_attenuationCallback;
		AnimationCurveCallback m_animationCurveCallback;
		ModelAnimationCallback m_modelAnimationCallback;
		SourceAnimationCallback m_sourceAnimationCallback;
		ReceiverAnimationCallback m_receiverAnimationCallback;
		AnimationsEqualizeCallback m_animationsEqualizeCallback;
		MeshVisualCallback m_meshVisualCallback;
	};

	/// <summary>
	/// Loads the scene from the scene description stored in .json format.
	/// </summary>
	/// <param name="stk">The main STK interface used to create resources and receive parsed data.</param>
	/// <param name="assetsDirectoryPath">Path to the directory with STK assets.</param>
	/// <param name="sceneFilePath">Relative path to the file with scene description.</param>
	/// <param name="callbacks">The callbacks which would be called with created resources and other information.</param>
	/// <note>The loader creates paths to resources by concatenation of assetsDirectoryPath
	/// and an appropriate resource file path.</note>
	/// <note>Use one of STK synchronization methods to ensure that all loading is actually finished.</note>
	void loadSceneJson(stk::ISoundToolKit& stk, stk::StringView assetsDirectoryPath,
		stk::StringView sceneFilePath, const SceneLoaderCallbacks& callbacks);
}

#endif
