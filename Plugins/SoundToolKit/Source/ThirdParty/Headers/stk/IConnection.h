///
/// \author Michal Radziszewski <michal.radziszewski@techmo.pl>
/// \date 31.10.2018
///
#ifndef STK__I_CONNECTION__H
#define STK__I_CONNECTION__H

namespace stk
{
	/// <summary>
	/// A connection returned by all anEvent.connectSomething(handler) methods.
	/// The connection can be disconnected manually, if needed.
	/// Otherwise it disconnects automatically during IConnection release.
	/// </summary>
	class IConnection
	{
		// public methods
	public:
		/// <summary>
		/// Releases the connection. Must be called once, and before Audio is released.
		/// </summary>
		virtual void release() = 0;

		/// <summary>
		/// Manually disconnects the connected handler from the event.
		/// </summary>
		virtual void disconnect() = 0;

		/// <summary>
		/// Checks if the handler is still connected.
		/// </summary>
		/// <note>
		/// The handler can be disconnected manually by disconnect(),
		/// or by the STK if the event is no longer relevant.
		/// </note>
		/// <returns>true if the handler is still connected, false otherwise.</returns>
		virtual bool isConnected() const = 0;

	protected:
		virtual ~IConnection() = default;
	};
}

#endif
