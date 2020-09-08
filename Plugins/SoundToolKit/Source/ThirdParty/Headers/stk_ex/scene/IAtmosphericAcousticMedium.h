///
/// \author Michal Radziszewski <michal.radziszewski@techmo.pl>
/// \date 22.02.2019
///
#ifndef STK_EX__SCENE__I_ATMOSPHERIC_ACOUSTIC_MEDIUM__H
#define STK_EX__SCENE__I_ATMOSPHERIC_ACOUSTIC_MEDIUM__H

#include <stk/UniqueResource.h>
#include <stk/SharedResource.h>
#include <stk/IEffect.h>

namespace stk
{
	class ISoundToolKit;
}

namespace stk_ex::scene
{
	/// <summary>
	/// Atmospheric acoustic medium assists in obtaining speed of sound and damping coefficients in air.
	/// </summary>
	class IAtmosphericAcousticMedium
	{
		// public construction and destruction methods
	public:

		/// <summary>
		/// Creates the atmospheric acoustic medium with the given parameters.
		/// </summary>
		/// <param name="temperature">Air temperature in Kelvins in (0K, INF) range.</param>
		/// <param name="pressure">Static atmospheric pressure in hPa in [950hPa, 1050hPa] range.</param>
		/// <param name="humidity">Relative humidity in percentage in [0, 100%] range.</param>
		static stk::UniqueResource<IAtmosphericAcousticMedium> create(
			stk::SharedResource<stk::ISoundToolKit> stk,
			float temperature = 293.15f, float pressure = 1013.25f, float humidity = 30.0f);

		// public methods
	public:

		/// <summary>
		/// Releases the atmospheric acoustic medium.
		/// </summary>
		virtual void release() = 0;

		/// <summary>
		/// Sets the temperature of air and updates medium properties.
		/// <summary>
		/// <param name="temperature">The temperature to set, in Kelvins, in (0K, INF) range.</param>
		virtual void setTemperature(float temperature) = 0;

		/// <summary>
		/// Gets the temperature of air.
		/// </summary>
		/// <returns>The obtained temperature in Kelvins.</returns>
		virtual float temperature() const = 0;

		/// <summary>
		/// Sets the static atmospheric pressure and updates medium properties.
		/// </summary>
		/// <param name="pressure">The pressure to set, in hPa, in [950hPa, 1050hPa] range.</param>
		virtual void setPressure(float pressure) = 0;

		/// <summary>
		/// Gets the static atmospheric pressure.
		/// </summary>
		/// <returns>The obtained pressure in hPa.</returns>
		virtual float pressure() const = 0;

		/// <summary>
		/// Sets the relative humidity and updates medium properties.
		/// </summary>
		/// <param name="humidity">The humidity to set, in percentage, in [0%, 100%] range.</param>
		virtual void setHumidity(float humidity) = 0;

		/// <summary>
		/// Gets the relative humidity.
		/// </summary>
		/// <returns>The obtained humidity as percentage.</returns>
		virtual float humidity() const = 0;

		/// <summary>
		/// Gets the air density calulated for given temperature, static pressure, and humidity.
		/// </summary>
		/// <returns>The obtained air density in [kg/m^3].</returns>
		virtual float density() const = 0;

		/// <summary>
		/// Gets the speed of sound in air calulated for given temperature, static pressure, and humidity.
		/// </summary>
		/// <returns>The obtained speed in [m/s].</returns>
		/// <note>The obtained speed can be provided to IAcousticMedium::setSpeedOfSound().</note>
		virtual float speedOfSoundInAir() const = 0;

		/// <summary>
		/// Gets the sound damping coefficients in air calulated for given temperature, static pressure, and humidity.
		/// </summary>
		/// <returns>The obtained sound damping coefficients.</returns>
		/// <note>The obtained coefficients can be provided to IAcousticMedium::dampingWithDistance().setCoefficients().</note>
		virtual const stk::IEffect::Coefficients& airDampingCoefficients() const = 0;

		// protected construction and destruction methods
	protected:

		virtual ~IAtmosphericAcousticMedium() = default;
	};
}

#endif
