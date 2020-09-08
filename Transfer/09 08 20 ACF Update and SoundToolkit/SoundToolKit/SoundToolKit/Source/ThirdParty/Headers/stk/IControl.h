///
/// \author Michal Radziszewski <michal.radziszewski@techmo.pl>
/// \date 27.10.2018
///
#ifndef STK__I_CONTROL__H
#define STK__I_CONTROL__H

#include <functional>
#include "UniqueResource.h"
#include "StringView.h"
#include "IConnection.h"

namespace stk
{
	class IIndicator;
	class ISetting;

	/// <summary>
	/// Allows to control the STK by settings and provides runtime information by indicators.
	/// </summary>
	class IControl
	{
		// public sub-types
	public:

		/// <summary>
		/// A handler to notify when a new engine setting is created.
		/// </summary>
		/// <param name="setting">The newly created setting.</param>
		/// <param name="value">The setting current value.</param>
		using OnSettingAddedHandler = std::function<void(ISetting& setting, StringView value)>;

		/// <summary>
		/// A handler to notify when a new engine indicator is created.
		/// </summary>
		/// <param name="indicator">The newly created indicator.</param>
		/// <param name="value">The indicator value.</param>
		using OnIndicatorAddedHandler = std::function<void(IIndicator& indicator, StringView value)>;

		/// <summary>
		/// A handler to notify when an engine indicator is removed.
		/// </summary>
		/// <note>The removed indicator is still valid during this notification. However, it must not be used afterwards.</note>
		/// <param name="indicator">The removed indicator.</param>
		using OnIndicatorRemovedHandler = std::function<void(IIndicator& indicator)>;

		// public methods
	public:

		/// <summary>
		/// Connects handler for new setting created notifications.
		/// The handler is called once for each setting registered so far as well.
		/// </summary>
		/// <note>There is no settingRemoved event, settings already added cannot be removed during lifetime of STK.</note>
		/// <param name="handler">A handler to notify when an STK setting is added.</param>
		/// <returns>An event connection, which can be used to disconnect from this event.</returns>
		virtual UniqueResource<IConnection> connectOnSettingAdded(OnSettingAddedHandler handler) = 0;

		/// <summary>
		/// Connects handler for new indicator created notifications.
		/// The handler is called once for each indicator registered so far as well.
		/// </summary>
		/// <param name="handler">A handler to notify when a new STK indicator is created.</param>
		/// <returns>An event connection, which can be used to disconnect from this event.</returns>
		virtual UniqueResource<IConnection> connectOnIndicatorAdded(OnIndicatorAddedHandler handler) = 0;

		/// <summary>
		/// Connects handler for indicator removed notifications.
		/// </summary>
		/// <param name="handler">A handler to notify when an STK indicator is removed.</param>
		/// <returns>An event connection, which can be used to disconnect from this event.</returns>
		virtual UniqueResource<IConnection> connectOnIndicatorRemoved(OnIndicatorRemovedHandler handler) = 0;

		// protected construction and destruction methods
	protected:
		virtual ~IControl() = default;
	};
}

#endif
