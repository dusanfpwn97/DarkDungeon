///
/// \author Michal Radziszewski <michal.radziszewski@techmo.pl>
/// \date 14.03.2019
///
#ifndef STK__I_SOURCE__H
#define STK__I_SOURCE__H

#include <functional>
#include "IResource.h"

namespace stk
{
	/// <summary>
	/// The public sound source interface - a base for ambient and spatial sound sources.
	/// </summary>
	class ISource: public virtual IResource
	{
		// public sub-types
	public:

		/// <summary>
		/// The callback called with the obtained state of one of playing, paused or stopped.
		/// </summary>
		using StateQueryCallback = std::function<void(bool value)>;

		/// <summary>
		/// The callback called with true if the source is muted or with false otherwise.
		/// </summary>
		using IsMutedCallback = std::function<void(bool isMuted)>;

		// public methods
	public:

		/// <summary>
		/// Asynchronously starts all paused, stopped, and new playbacks associated with this source.
		/// </summary>
		virtual void play() = 0;

		/// <summary>
		/// Asynchronously pauses all playing playbacks associated with this source.
		/// </summary>
		virtual void pause() = 0;

		/// <summary>
		/// Asynchronously stops all playing and paused playbacks associated with this source.
		/// </summary>
		virtual void stop() = 0;

		/// <summary>
		/// Checks if at least one playback associated with this source is currently playing.
		/// </summary>
		/// <param name="callback">The callback called with the query result.</param>
		virtual void isPlaying(StateQueryCallback callback) = 0;

		/// <summary>
		/// Checks if all playbacks associated with this source are currently paused.
		/// </summary>
		/// <param name="callback">The callback called with the query result.</param>
		virtual void isPaused(StateQueryCallback callback) = 0;

		/// <summary>
		/// Checks if all playbacks associated with this source are currently stopped.
		/// Sources with no playbacks associated are considered being stopped.
		/// </summary>
		/// <param name="callback">The callback called with the query result.</param>
		virtual void isStopped(StateQueryCallback callback) = 0;

		/// <summary>
		/// Synchronously sets the volume of the sound source. The STK engine uses hierarchical volume representation,
		/// i.e. global, sound source class, sound source, and playback. The final volume to scale the sound in a
		/// specific playback is affected by multiplication of the volume at all of these four volumes.
		/// </summary>
		/// <param name="volume">The volume to set. Must be a finite, non-negative value.</param>
		virtual void setVolume(float volume) = 0;

		/// <summary>
		/// Gets the volume of the sound source.
		/// </summary>
		/// <returns>The current volume of the sound source.</returns>
		virtual float volume() const = 0;

		/// <summary>
		/// Asynchronously mutes the sound source. Any muted source does not emit sound,
		/// but retains its volume unchanged and any playbacks associated with it are not paused.
		/// </summary>
		virtual void mute() = 0;

		/// <summary>
		/// Asynchronously unmutes the sound source.
		/// </summary>
		virtual void unmute() = 0;

		/// <summary>
		/// Checks if the source is muted.
		/// </summary>
		/// <param name="callback">The callback called with true if the source is muted or with false otherwise.</param>
		virtual void isMuted(IsMutedCallback callback) = 0;

		// protected construction and destruction methods
	protected:
		virtual ~ISource() = default;
	};
}

#endif
