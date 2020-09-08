///
/// \author Michal Radziszewski <michal.radziszewski@techmo.pl>
/// \date 10.12.2018
///
#ifndef STK__I_EFFECT__H
#define STK__I_EFFECT__H

#include <cstddef>
#include <array>
#include <functional>

namespace stk
{
	/// <summary>
	/// Controls an effect within acoustic material: absorption, scattering, transmission,
	/// or sound damping effect in acoustic medium.
	/// It allows enabling, disabling, and setting coefficients for the effect.
	/// Disabling scattering or transmission means that these effects are not simulated.
	/// Disabling absorption means that the material reflects or transmits all wave energy.
	/// Disabling all three effects means that material reflects specularly all wave energy.
	/// Disabling damping in medium means that sound wave does not decrease its energy
	/// with distance.
	/// </summary>
	class IEffect
	{
		// public sub-types
	public:

		/// <summary>
		/// Number of frequency bands in STK frequency responses and acoustic effects.
		/// </summary>
		static constexpr size_t FrequencyBandsCount = 8u;

		/// <summary>
		/// The storage for definition of frequency bands used within STK.
		/// </summary>
		using FrequencyInfo = std::array<float, FrequencyBandsCount>;

		/// <summary>
		/// Center frequencies of octave bands used in filtering (https://en.wikipedia.org/wiki/Octave_band)
		/// </summary>
		static constexpr FrequencyInfo FrequencyBands =
			{ {125.0f, 250.0f, 500.0f, 1000.0f, 2000.0f, 4000.0f, 8000.0f, 16000.0f} };

		/// <summary>
		/// The coefficients for computing frequency response for the given acoustic effect.
		/// The equations describing how STK computes frequency responses are given in documentation.
		/// </summary>
		using Coefficients = std::array<float, FrequencyBandsCount>;

		/// <summary>
		/// A callback called with enabled/disabled status after isEnabled() call.
		/// </summary>
		using IsEnabledCallback = std::function<void(bool isEnabled)>;

		/// <summary>
		/// A callback called with obtained coefficients after getCoefficients() call.
		/// </summary>
		using CoefficientsCallback = std::function<void(const Coefficients& coefficients)>;

		// public methods
	public:

		/// <summary>
		/// Enables the effect on parent material or acoustic medium.
		/// </summary>
		virtual void enable() = 0;

		/// <summary>
		/// Disables the effect on parent material or acoustic medium.
		/// </summary>
		virtual void disable() = 0;

		/// <summary>
		/// Checks if the effect on parent material or acoustic medium is enabled.
		/// </summary>
		/// <param name="callback">A callback called with true if the effect is enabled, with false otherwise.</param>
		virtual void isEnabled(IsEnabledCallback callback) = 0;

		/// <summary>
		/// Sets the effect coefficients. Coefficients are defined for respective bands.
		/// They define how strong the effect is: for materials in [0, 1] range, from off to full-on,
		/// and in [0, INF) range in air damping, from no damping to maximum damping.
		/// Specifying any coefficient outside the range causes the call to have no effect.
		/// </summary>
		/// <param name="coefficients">The coefficients to set.</param>
		virtual void setCoefficients(const Coefficients& coefficients) = 0;

		/// <summary>
		/// Gets the effect coefficients. The call is asynchronous, i.e. given callback
		/// with requested coefficients is called during flush or finish.
		/// </summary>
		/// <param name="callback">A callback called with the requested coefficients.</param>
		virtual void getCoefficients(CoefficientsCallback callback) = 0;
	};
}

#endif
