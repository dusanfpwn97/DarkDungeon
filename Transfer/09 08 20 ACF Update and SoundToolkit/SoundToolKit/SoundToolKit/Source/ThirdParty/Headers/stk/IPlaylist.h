///
/// \author Michal Radziszewski <michal.radziszewski@techmo.pl>
/// \date 14.02.2019
///
#ifndef STK__I_PLAYLIST__H
#define STK__I_PLAYLIST__H

#include <functional>
#include "SharedResource.h"
#include "ArrayView.h"
#include "PlaylistItem.h"
#include "ISampleStatic.h"

namespace stk
{
	/// <summary>
	/// Interface of playlists for playing many samples or other playlists at once.
	/// </summary>
	class IPlaylist: public virtual ISampleStatic
	{
		// public sub-types
	public:

		/// <summary>
		/// A callback called with a view on obtained playlist's items.
		/// </summary>
		/// <param name="meshes">The obtained view on all playlist's items.</param>
		using GetItemsCallback = std::function<void(ArrayView<PlaylistItem> items)>;

		// public methods
	public:

		/// <summary>
		/// Asynchronously calls the provided callback with a view on all playlist's items.
		/// </summary>
		/// <param name="callback">The callback to be called with a view on playlist's items.</param>
		virtual void getItems(GetItemsCallback callback) = 0;

		// protected construction and destruction methods
	protected:
		virtual ~IPlaylist() = default;
	};
}

#endif
