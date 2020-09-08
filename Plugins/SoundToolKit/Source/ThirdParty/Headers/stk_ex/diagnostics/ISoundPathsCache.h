///
/// \author Michal Radziszewski <michal.radziszewski@techmo.pl>
/// \date 11.04.2019
///
#ifndef STK_EX__DIAGNOSTICS__I_SOUND_PATHS_CACHE__H
#define STK_EX__DIAGNOSTICS__I_SOUND_PATHS_CACHE__H

#include <functional>
#include <stk/UniqueResource.h>
#include <stk/SharedResource.h>
#include <stk/Math.h>
#include <stk/ArrayView.h>
#include <stk/PathVertexType.h>

namespace stk
{
	class ISoundToolKit;
}

namespace stk_ex::diagnostics
{
	/// <summary>
	/// An utility for caching of sound paths for diagnostic visualization purposes.
	/// </summary>
	class ISoundPathsCache
	{
		// public sub-types
	public:

		/// <summary>
		/// A vertex of a sound path - its position in space and its type.
		/// </summary>
		struct SoundPathVertex
		{
			stk::vec3 position;
			stk::PathVertexType type;
		};

		/// <summary>
		/// A view on a complete sound path.
		/// Any path starts with source vertex, ends with receiver vertex, and has zero or more effects in the middle.
		/// </summary>
		using SoundPathView = stk::ArrayView<SoundPathVertex>;

		/// <summary>
		/// A callback called with a view on all cached sound paths.
		/// </summary>
		/// <param name="paths">The obtained sound paths.</param>
		using SoundPathsCallback = std::function<void(stk::ArrayView<SoundPathView> paths)>;

		// public construction and destruction methods
	public:

		/// <summary>
		/// Creates the sound paths cache interface.
		/// </summary>
		/// <param name="stk">The main STK interface used to query for the diagnositcs data.</param>
		/// <returns>The newly created sound paths cache or NULL pointer in case of an error.</param>
		static stk::UniqueResource<ISoundPathsCache> create(stk::SharedResource<stk::ISoundToolKit> stk);

		// public methods
	public:

		/// <summary>
		/// Releases the sound paths cache.
		/// </summary>
		virtual void release() = 0;

		/// <summary>
		/// Obtains the view on all cached sound paths.
		/// </summary>
		/// <note>The null view is returned if paths caching is disabled.</note>
		/// <note>The callback is not called if paths caching is enabled, and no sound frame has been completed
		/// since the last call to this function. The sound frames are computed by STK on user demand by
		/// the computeSoundFrame() calls.</note>
		/// <note>The callback is synchronized, i.e. the method is blocking sound paths generation, so callback
		/// should return as soon as possible, it should just store the data and not display it.</note>
		/// <param name="callback">The callback called with the obtained view on cached paths.</param>
		virtual void getCachedPaths(SoundPathsCallback callback) = 0;

		/// <summary>
		/// Enables caching of sound paths.
		/// </summary>
		virtual void enableCaching() = 0;

		/// <summary>
		/// Disables caching of sound paths.
		/// </summary>
		virtual void disableCaching() = 0;

		/// <summary>
		/// Checks if caching of sound paths is enabled.
		/// </summary>
		/// <returns>True if caching is enabled, false otherwise.</returns>
		virtual bool isCachingEnabled() const = 0;

		// protected construction and destruction methods
	protected:

		~ISoundPathsCache() = default;
	};
}

#endif
