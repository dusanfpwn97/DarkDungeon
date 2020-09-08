///
/// \author Michal Radziszewski <michal.radziszewski@techmo.pl>
/// \date 27.10.2018
///
#ifndef STK__I_SETTING__H
#define STK__I_SETTING__H

#include <functional>
#include "UniqueResource.h"
#include "StringView.h"
#include "SettingType.h"
#include "IConnection.h"

namespace stk
{
	/// <summary>
	/// The public interface to a particular engine setting.
	/// </summary>
	class ISetting
	{
		// public sub-types
	public:
		/// <summary>
		/// Handler called as an confirmation of setting value being finished.
		/// </summary>
		/// <param name="currentValue">
		/// The current Setting value (the new Setting value if update succeds, or its original value otherwise).
		/// </param>
		using OnSetValueFinishedHandler = std::function<void(StringView currentValue)>;

		// public methods
	public:
		/// <summary>
		/// All STK engine Settings have names with the following convention:
		/// group.settingName, where the group is an aggregate of sub-groups, for example:
		/// stk.geometry.beamPropagation.enableDiffraction is the engine setting used to enable or disable
		/// the diffraction simulation.
		/// </summary>
		/// <returns>The setting name.</returns>
		virtual StringView name() const = 0;

		/// <summary>
		/// A more detailed description of meaning of this particular Setting.
		/// Optional, can be an empty string.
		/// </summary>
		/// <returns>The Setting description.</returns>
		virtual StringView description() const = 0;

		/// <summary>
		/// The type of the Setting, a simple variable like bool or int, or an list of ints or floats.<int>
		/// </summary>
		/// <returns>The type of the Setting value.</returns>
		virtual SettingType type() const = 0;

		/// <summary>
		/// The set of allowed values of the Setting. It is displayed according to the Setting type:
		/// - {false, true} for logical settings (always)
		/// - {enumVal1, enumVal2, ..., enumValN} for enumerable settings
		/// - [min, max] always closed intervals for integral settings
		/// - [min, max) open or closed intervals for floating point settings
		/// - interval^count ([min, max]^{n..m}) for lists of integers or floats,
		///   e.g. [-10, 10]^{2..5} means 2 to 5 numbers in range [-10, 10]
		///   a) empty string when n == 0 && m == 0
		///   b) interval only when n == 1 && m == 1, e.g. [0, 1]
		///   c) simplifeid count when n == m, e.g. [-1, 1]^8 means exactly 8 numbers from [-1, 1] range
		///   d) full format otherwise, e.g [-10, 10]^{2..5}
		/// </summary>
		/// <returns>The allowed values of the Setting in the string form.</returns>
		virtual StringView allowedValues() const = 0;

		/// <summary>
		/// Returns the default value of the Setting.
		/// </summary>
		/// <returns>The default value of the Setting.</returns>
		virtual StringView defaultValue() const = 0;

		/// <summary>
		/// Asynchronously returns the current value of the Setting. Calling finish()
		/// just after currentValue() synchronizes the engine and guarantees the callback is called.
		/// </summary>
		/// <param name="callback">The callback called with current value of the setting.</param>
		virtual void currentValue(std::function<void(StringView)> callback) const = 0;

		/// <summary>
		/// Asynchronously sets the new value for this setting. Calls a hadler registered by
		/// connectOnSetValueFinished after either succesful or unsuccesful value change.
		/// </summary>
		/// <param name="newValue">
		/// The new value to set for this setting.
		/// </param>
		virtual void setValue(StringView newValue) = 0;

		/// <summary>
		/// Connects handler for the confirmation of setValue event.
		/// </summary>
		/// <param name="handler">A handler to call when the setValue has been finished.</param>
		/// <returns>An event connection, which can be used to disconnect from this event.</returns>
		[[nodiscard]] virtual UniqueResource<IConnection> connectOnSetValueFinished(
			OnSetValueFinishedHandler handler) = 0;

		// protected construction and destruction methods
	protected:
		virtual ~ISetting() = default;
	};
}

#endif
