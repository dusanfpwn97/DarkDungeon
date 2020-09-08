///
/// \author Michal Radziszewski <michal.radziszewski@techmo.pl>
/// \date 31.07.2018
///
#ifndef STK__SETTING_TYPE__H
#define STK__SETTING_TYPE__H

namespace stk
{
	///<summary>
	///The type of a Setting. It could be a single variable like bool, enum, signed int, or float.
	///Alternatively, it can be a list of signed ints or floats.
	///Values of settings are internally parsed from strings passed to STK.
	///Booleans can be parsed as "true"/"false", "True"/"False", "TRUE"/"FALSE", or "1"/"0".
	///Values of enumerations are stored as strings with strictly defined values.
	///Signed integers and floats are always parsed to 32 bit numbers.
	///Lists are whitespace-separated lists of integer or floating point numbers.
	///All whitespaces at the beginning and at the end of any value are ignored.
	///In the middle of any non-list value (in particular enumerations) whitespaces are prohibited.
	///</summary>
	enum class SettingType: int
	{
		Boolean     = 0x01,
		Enumeration = 0x02,
		Integer     = 0x03,
		Float       = 0x04,

		ListOfIntegers = 0x13,
		ListOfFloats   = 0x14
	};
}

#endif
