///
/// \author Michal Radziszewski <michal.radziszewski@techmo.pl>
/// \date 28.11.2018
///
#ifndef STK__I_PLAYBACK__H
#define STK__I_PLAYBACK__H

#include <functional>
#include "UniqueResource.h"
#include "SharedResource.h"
#include "IResource.h"
#include "IConnection.h"
#include "PlaybackParameters.h"

namespace stk
{
	class ISample;
	class ISource;

	/// <summary>
	/// Controls playback - an act of playing a sound sample from a sound source. All the updates are recorded and executed after an engine flush.
	/// </summary>
	class IPlayback: public virtual IResource
	{
		// public sub-types
	public:
		using PlaybackEventHandler = std::function<void(IPlayback&)>;

		// public methods
	public:

		/// <summary>
		/// Queries the playback for the sample with which the playback was created.
		/// </summary>
		/// <returns>The sample used to create this playback.</returns>
		virtual SharedResource<ISample> sample() const = 0;

		/// <summary>
		/// Queries the playback for the sound source with which the playback was created.
		/// </summary>
		/// <returns>The sound source used to create this playback.</returns>
		virtual SharedResource<ISource> source() const = 0;

		/// <summary>
		/// Queries the playback for parameters used to create it.
		/// </summary>
		/// <returns>The playback parameters: begin, end, and repeat count.</returns>
		virtual PlaybackParameters parameters() const = 0;

		/// <summary>
		/// Starts sound emission in the point the playback was paused or at the beginning if it is a new playback or it was stopped.
		/// </summary>
		virtual void play() = 0;

		/// <summary>
		/// Pauses sound emission.
		/// </summary>
		virtual void pause() = 0;

		/// <summary>
		/// Stops sound emission. The playback would be rewound to the beginning during next play() call.
		/// </summary>
		virtual void stop() = 0;

		/// <summary>
		/// Checks if playback is playing now.
		/// </summary>
		/// <returns>True is playing now, false otherwise.</returns>
		virtual bool isPlaying() = 0;

		/// <summary>
		/// Checks if playback is stopped.
		/// </summary>
		/// <returns>True if playback is stopped now, false otherwise.</returns>
		virtual bool isStopped() = 0;

		/// <summary>
		/// Checks if playback is paused.
		/// </summary>
		/// <returns> True if playback is paused now, false otherwise.</returns>
		virtual bool isPaused() = 0;

		/// <summary>
		/// Synchronously sets the volume of the playback. The STK engine uses hierarchical volume representation,
		/// i.e. global, sound source class, sound source, and playback. The final volume to scale the sound in a
		/// specific playback is affected by multiplication of the volume at all of these four volumes.
		/// </summary>
		/// <param name="volume">The volume to set. Must be a finite, non-negative value.</param>
		virtual void setVolume(float volume) = 0;

		/// <summary>
		/// Gets the playback volume.
		/// </summary>
		/// <returns>The current volume value.</returns>
		virtual float volume() = 0;

		/// <summary>
		/// Connects handler for playback start and resume notifications.
		/// </summary>
		/// <param name="handler">A handler to notify when the playback is resumed or started from the beginning.</param>
		/// <returns>An event connection, which can be used to disconnect from this event.</returns>
		virtual UniqueResource<IConnection> connectOnStarted(PlaybackEventHandler handler) = 0;

		/// <summary>
		/// Connects handler for playback end notifications.
		/// </summary>
		/// <param name="handler">A handler to notify when the playback ends.</param>
		/// <returns>An event connection, which can be used to disconnect from this event.</returns>
		virtual UniqueResource<IConnection> connectOnEnded(PlaybackEventHandler handler) = 0;

		/// <summary>
		/// Connects handler for playback pause notifications.
		/// </summary>
		/// <param name="handler">A handler to notify when the playback is paused.</param>
		/// <returns>An event connection, which can be used to disconnect from this event.</returns>
		virtual UniqueResource<IConnection> connectOnPaused(PlaybackEventHandler handler) = 0;

		// protected construction and destruction methods
	protected:
		virtual ~IPlayback() = default;
	};
}

#endif
