///
/// \author Michal Radziszewski <michal.radziszewski@techmo.pl>
/// \date 17.10.2018
///
#ifndef STK__I_FENCE__H
#define STK__I_FENCE__H

#include <cstdint>

namespace stk
{
	/// <summary>
	/// A fence synchronization primitive, created by Audio::fenceSynchronize().
	/// The fence can be waited for Audio to finish execution of all commands issued *before* fence creation.
	/// The fence must be released when is no longer needed.
	/// </summary>
	class IFence
	{
		// public sub-types
	public:
		/// <summary>
		/// Type to use when a function needs a time duration.
		/// </summary>
		using microseconds = uint64_t;

		// public methods
	public:
		/// <summary>
		/// Releases the fence. Must be called once, and before Audio is released.
		/// </summary>
		virtual void release() = 0;

		/// <summary>
		/// Flushes Audio commands and waits (does not return) until the Audio commands scheduler passes the fence.
		/// </summary>
		virtual void wait() = 0;

		/// <summary>
		/// Flushes Audio commands and waits (does not return) until either the Audio commands scheduler passes the fence or timeout expires.
		/// </summary>
		/// <param name="timeout">The time in microseconds after the waiting is aborted.</param>
		/// <returns>true if wait has been succesful, false if timeout expired or error occured.</returns>
		virtual bool waitForAtMost(microseconds timeout) = 0;

		// protected construction and destruction methods
	protected:
		virtual ~IFence() = default;
	};
}

#endif
