///
/// \author Michal Radziszewski <michal.radziszewski@techmo.pl>
/// \date 18.02.2019
///
#ifndef STK__PLAYLIST_ITEM__H
#define STK__PLAYLIST_ITEM__H

#include "SharedResource.h"
#include "PlaybackParameters.h"

namespace stk
{
	class ISampleStatic;

	/// <summary>
	/// Description of item in playlist - its sound data and playback parameters.
	/// </summary>
	struct PlaylistItem
	{
		SharedResource<ISampleStatic> sample;
		PlaybackParameters parameters;
	};
}

#endif
