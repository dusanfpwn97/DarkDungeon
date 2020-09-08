///
/// \author Michal Radziszewski <michal.radziszewski@techmo.pl>
/// \date 02.12.2018
///
#ifndef STK__I_DIRECTIVITY__H
#define STK__I_DIRECTIVITY__H

#include "DirectivityDataTypes.h"
#include "Math.h"
#include "IResource.h"

namespace stk
{
	/// <summary>
	/// Controls a specific directivity model.
	/// A directivity model imposed on a sound source changes, how the sound is emitted depending on the direction.
	/// </summary>
	class IDirectivity: public virtual IResource
	{
		// public methods
	public:

		/// <param name="symmetryType">
		/// Symmetry of characteristics. See enum description.
		/// </param>
		virtual void setSymmetryType(DirectivitySymmetry symmetryType) = 0;

		/// <returns>
		/// Symmerty of characteristics. See description of enum DirectivitySymmetry.
		/// </returns>
		virtual DirectivitySymmetry getSymmetryType() const = 0;

		// TODO re-enable this in task #509
		/// <param name="rotation">
		/// Quaternion, which will rotate given characteristic. Default Forward direction is (0,0,1) -> Z axis
		/// </param>
		//virtual void setForward(Rotation rotation) = 0;

		// TODO re-enable this in task #509
		/// <returns>
		/// Forward rotation of directivity characteristic. Usually highest amplitude gain occurs at this direction.
		/// </returns>
		//virtual Rotation getForward() const = 0;

		/// <param name="angle">
		/// Resolution of angular data points in deegrees.
		/// </param>
		virtual void setAngularDataResolution(int angle) = 0;

		/// <returns>
		/// Resolution of angular data points in deegrees.
		/// </returns>
		virtual int getAngularDataResolution() const = 0;

		/// <param name="direction">
		/// Direction, on which the gain occurs.
		/// </param>
		/// <param name="data">
		/// Array of amplitude gains for 8 octave bands, in given direction. Bands are between 125Hz and 16kHz.
		/// </param>
		virtual void setDirectivityData(Direction direction, DirectivityData data) = 0;

		// TODO re-enable this in task #509
		/// <param name="direction">
		/// Direction, on which the gain occurs.
		/// </param>
		/// <returns>
		/// Array of amplitude gains for 8 octave bands, in given direction. Bands are between 125Hz and 16kHz.
		/// </returns>
		//virtual DirectivityData getDirectivityData(Direction direction) const = 0;

		// protected construction and destruction methods
	protected:
		virtual ~IDirectivity() = default;
	};
}

#endif
