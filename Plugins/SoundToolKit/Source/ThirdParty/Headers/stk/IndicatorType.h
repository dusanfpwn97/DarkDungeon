///
/// \author Michal Radziszewski <michal.radziszewski@techmo.pl>
/// \date 21.08.2018
///
#ifndef STK__INDICATOR_TYPE__H
#define STK__INDICATOR_TYPE__H

namespace stk
{
	/// <summary>
	/// The type of an indicator. It can be any of:
	/// - Bool - a logical value (true or false)
	/// - UInt64 - a 64 bit integer number typically used for storing counters' values,
	/// - Float - an arbitrary 32 bit floating point number,
	/// - String - an arbitrary string.
	/// </summary>
	enum class IndicatorType: int
	{
		Boolean = 0x01,
		UInt64  = 0x02,
		Float   = 0x03,
		String  = 0x04
	};
}

#endif
