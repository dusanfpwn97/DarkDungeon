///
/// \author Michal Radziszewski <michal.radziszewski@techmo.pl>
/// \date 21.08.2018
///
#ifndef STK__INDICATOR_UNITS__H
#define STK__INDICATOR_UNITS__H

namespace stk
{
	/// <summary>
	/// The units of an indicator value. It can be any of:
	/// - None - for simple counters and arbitrary strings,
	/// - Microseconds - for delta time counters,
	/// - Percentage - for floats restricted to [0, 100] range.
	/// </summary>
	enum class IndicatorUnits: int
	{
		None         = 0,
		Microseconds = 1,
		Decibels     = 2,
		Percentage   = 3
	};
}

#endif
