///
/// \author Michal Radziszewski <michal.radziszewski@techmo.pl>
/// \date 27.10.2018
///
#ifndef STK__I_INDICATOR__H
#define STK__I_INDICATOR__H

#include <functional>
#include "UniqueResource.h"
#include "StringView.h"
#include "IndicatorType.h"
#include "IndicatorUnits.h"
#include "IConnection.h"

namespace stk
{
	/// <summary>
	/// The public interface to a particular engine indicator.
	/// </summary>
	class IIndicator
	{
		// public sub-types
	public:
		/// <summary>
		/// The callback called when engine changes the indicator value.
		/// </summary>
		/// <param name="indicator">Indicator which value has been changed.</param>
		/// <param name="newValue">The new indicator value.</param>
		using OnValueChangedEventHandler = std::function<void(IIndicator& indicator, StringView newValue)>;

		// public methods
	public:
		/// <summary>
		/// All STK engine indicators have names with the following convention:
		/// group.indicatorName, where the group is an aggregate of sub-groups, for example:
		/// stk.audioEngine.frameUpdateTime is the indicator used to show how much time
		/// is consumed by updating sound frame.
		/// </summary>
		/// <returns>The indicator name.</returns>
		virtual StringView name() const = 0;

		/// <summary>
		/// A more detailed description of meaning of this particular indicator.
		/// Optional, can be an empty string.
		/// </summary>
		/// <returns>The indicator description.</returns>
		virtual StringView description() const = 0;

		/// <summary>
		/// The type of the indicator: Bool, UInt64, Float, or String.
		/// </summary>
		/// <returns>The indicator type.</returns>
		virtual IndicatorType type() const = 0;

		/// <summary>
		/// The units of the indicator value: None, Microseconds, Decibels, or Percentage.
		/// Bool and String indicators always return None.
		/// </summary>
		/// <returns>The indicator units.</returns>
		virtual IndicatorUnits units() const = 0;

		/// <summary>
		/// Connects handler for indicator value changed events.
		/// Since the setting might have its value changed after it is created and before the connection
		/// is performed, the handler would be called once just after the connection. All the subsequent
		/// calls would occur only after indicator actually changes its value.
		/// </summary>
		/// <param name="handler">A handler to notify when the value of this indicator is changed.</param>
		/// <returns>An event connection, which can be used to disconnect from this event.</returns>
		[[nodiscard]] virtual UniqueResource<IConnection> connectOnValueChanged(
			OnValueChangedEventHandler handler) = 0;

		// protected construction and destruction methods
	protected:
		virtual ~IIndicator() = default;
	};

}

#endif
