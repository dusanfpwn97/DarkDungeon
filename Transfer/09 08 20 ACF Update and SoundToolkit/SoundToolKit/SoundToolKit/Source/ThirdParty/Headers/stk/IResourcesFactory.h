///
/// \author Michal Radziszewski <michal.radziszewski@techmo.pl>
/// \date 19.02.2019
///
#ifndef STK__I_RESOURCES_FACTORY__H
#define STK__I_RESOURCES_FACTORY__H

#include "ArrayView.h"
#include "AudioBufferInterleavedView.h"
#include "AudioBufferDeinterleavedView.h"
#include "PlaylistItem.h"
#include "SharedResource.h"

namespace stk
{
	class IMaterial;
	class IMesh;
	class IModel;
	class ISample;
	class ISampleStatic;
	class ISampleStreaming;
	class IPlaylist;
	class IDirectivity;
	class ISource;
	class ISourceAmbient;
	class ISourceAmbientSeparatelyOutput;
	class ISourceSpatial;
	class ISourceSpatialSeparatelyOutput;
	class IPlayback;

	/// <summary>
	/// The factory is responsible for creating all STK resources.
	/// </summary>
	class IResourcesFactory
	{
		// public methods
	public:
		/// <summary>
		/// Creates a new acoustic material resource initialized with default values.
		/// </summary>
		/// <returns>The created material or null pointer in case of an error.</returns>
		virtual SharedResource<IMaterial> createMaterial() = 0;

		/// <summary>
		/// Creates an empty mesh resource which uses a default acoustic material.
		/// </summary>
		/// <returns>The created mesh or null pointer in case of an error.</returns>
		virtual SharedResource<IMesh> createMesh() = 0;

		/// <summary>
		/// Creates a model resource comprised of the given meshes.
		/// </summary>
		/// <param name="meshes">The view on meshes used to create the model.</param>
		/// <returns>The created model or null pointer in case of an error.</returns>
		virtual SharedResource<IModel> createModel(ArrayView<SharedResource<IMesh>> meshes) = 0;

		/// <summary>
		/// Creates a static sound sample resource initialized to the given sound data.
		/// </summary>
		/// <param name="view">A view on an interleaved buffer containing sound data.</param>
		/// <returns>The created static sound sample or null pointer in case of an error.</returns>
		virtual SharedResource<ISampleStatic> createSampleStatic(AudioBufferInterleavedView view) = 0;

		/// <summary>
		/// Creates a static sound sample resource initialized to the given sound data.
		/// </summary>
		/// <param name="view">A view on a buffer containing sound data.</param>
		/// <returns>The created static sound sample or null pointer in case of an error.</returns>
		virtual SharedResource<ISampleStatic> createSampleStatic(AudioBufferDeinterleavedView view) = 0;

		/// <summary>
		/// Creates a streaming sound sample resource.
		/// </summary>
		/// <param name="numberOfChannels">Number of channels for the created sample.</param>
		/// <returns>The created streaming sound sample.</returns>
		virtual SharedResource<ISampleStreaming> createSampleStreaming(size_t numberOfChannels = 1u) = 0;

		/// <summary>
		/// Creates playlist which can be used to play samples or other playlists one after another.
		/// </summary>
		/// <param name="items">The items which are used to create the playlist.</param>
		/// <returns>The created playlist.</returns>
		virtual SharedResource<IPlaylist> createPlaylist(ArrayView<PlaylistItem> items) = 0;

		/// <summary>
		/// Creates a directivity model.
		/// </summary>
		/// <returns>The created directivity model.</returns>
		virtual SharedResource<IDirectivity> createDirectivity() = 0;

		/// <summary>
		/// Creates an ambient soud source.
		/// </summary>
		/// <returns>The created source.</returns>
		virtual SharedResource<ISourceAmbient> createAmbientSoundSource() = 0;

		/// <summary>
		/// Creates an ambient sound source which audio samples are not mixed with other sources on the scene
		/// but rendered separately.
		/// </summary>
		/// <returns>The created separately output ambient source.</returns>
		virtual SharedResource<ISourceAmbientSeparatelyOutput> createSeparatelyOutputAmbientSoundSource() = 0;

		/// <summary>
		/// Creates a spatial soud source.
		/// </summary>
		/// will be mixed with other sound sources on the scene or rendered separately.</param>
		/// <returns>The created source.</returns>
		virtual SharedResource<ISourceSpatial> createSpatialSoundSource() = 0;

		/// <summary>
		/// Creates an spatial sound source which audio samples are not mixed with other sources on the scene
		/// but rendered separately.
		/// </summary>
		/// <returns>The created separately output spatial source.</returns>
		virtual SharedResource<ISourceSpatialSeparatelyOutput> createSeparatelyOutputSpatialSoundSource() = 0;

		/// <summary>
		/// Creates a playback which uses the given sample and the given sound source.
		/// </summary>
		/// <param name="sample">The sound sample to be emitted by this playback.</param>
		/// <param name="source">The sound source used to emit the sound.</param>
		/// <returns>Playback representing the process of playing given sound in the given source.</returns>
		virtual SharedResource<IPlayback> createPlayback(SharedResource<ISample> sample, SharedResource<ISource> source) = 0;

		/// <summary>
		/// Creates a playback which uses the given sample and the given sound source.
		/// </summary>
		/// <param name="sample">The sound sample to be emitted by this source. </param>
		/// <param name="source">The sound source used to emit the sound.</param>
		/// <param name="parameters">Specifies trimming and repeat count of the sample.</param>
		/// <returns>Playback representing the process of playing given sound in this source.</returns>
		virtual SharedResource<IPlayback> createPlayback(SharedResource<ISampleStatic> sample, SharedResource<ISource> source,
			const PlaybackParameters& parameters) = 0;

		// protected construction and destruction methods
	protected:
		virtual ~IResourcesFactory() = default;
	};
}

#endif
