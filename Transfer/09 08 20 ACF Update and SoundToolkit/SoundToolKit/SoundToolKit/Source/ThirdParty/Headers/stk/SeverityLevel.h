///
/// \author Michal Radziszewski <michal.radziszewski@techmo.pl>
/// \date 14.08.2018
///
#ifndef STK__SEVERITY_LEVEL__H
#define STK__SEVERITY_LEVEL__H

namespace stk
{
	/// <summary>
	/// Severity levels of STK logs:
	/// - Info: just information
	/// - Warning: something is wrong, but the STK is still able to produce output
	/// - Error: something serious happened in STK internals, the STK is unstable and should be rebooted
	/// <!summary>
	enum class SeverityLevel: int
	{
		Info = 0,
		Warning = 1,
		Error = 2
	};
}

#endif
