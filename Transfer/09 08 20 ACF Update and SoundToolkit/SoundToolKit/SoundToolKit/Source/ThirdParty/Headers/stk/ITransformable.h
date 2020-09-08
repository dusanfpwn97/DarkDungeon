///
/// \author Michal Radziszewski <michal.radziszewski@techmo.pl>
/// \date 22.01.2019
///
#ifndef STK__I_TRANSFORMABLE__H
#define STK__I_TRANSFORMABLE__H

#include <functional>
#include "Math.h"

namespace stk
{
	/// <summary>
	/// Allows uniform control of position, orientation, and velocity of all transformable STK scene elements.
	/// </summary>
	class ITransformable
	{
		// public sub-types
	public:

		/// <summary>
		/// A callback called with the obtained position of the transformable scene element.
		/// </summary>
		/// <param name="position">The obtained position.</param>
		using GetPositionCallback = std::function<void(const vec3& position)>;

		/// <summary>
		/// A callback called with the obtained orientation of the transformable scene element.
		/// </summary>
		/// <param name="orientation">The obtained orientation.</param>
		using GetOrientationCallback = std::function<void(const quaternion& orientation)>;

		/// <summary>
		/// A callback called with the obtained linear velocity of the transformable scene element.
		/// </summary>
		/// <param name="linearVelocity">The obtained linear velocity.</param>
		using GetLinearVelocityCallback = std::function<void(const vec3& linearVelocity)>;

		/// <summary>
		/// A callback called with the obtained angular velocity of the transformable scene element.
		/// </summary>
		/// <param name="angularVelocity">
		/// The obtained angular velocity.
		/// The vector direction defines the axis of rotation, and its length defines how fast the rotation is.
		/// </param>
		using GetAngularVelocityCallback = std::function<void(const vec3& angularVelocity)>;

		// public methods
	public:

		/// <summary>
		/// Asynchronously sets position of the transformable scene element.
		/// </summary>
		/// <param name="position">The position to set.</param>
		virtual void setPosition(const vec3& position) = 0;

		/// <summary>
		/// Asynchronously obtains position of the transformable scene element.
		/// </summary>
		/// <param name="callback">The callback called with the obtained position.</param>
		virtual void position(GetPositionCallback callback) = 0;

		/// <summary>
		/// Asynchronously sets orientation of the transformable scene element.
		/// </summary>
		/// <param name="orientation">The orientation to set.</param>
		virtual void setOrientation(const quaternion& orientation) = 0;

		/// <summary>
		/// Asynchronously obtains orientation of the transformable scene element.
		/// </summary>
		/// <param name="callback">The callback called with the obtained orientation.</param>
		virtual void orientation(GetOrientationCallback callback) = 0;

		/// <summary>
		/// Asynchronously sets both the position and the orientation together.
		/// </summary>
		/// <note>This method is faster than setting the position and the orientation independently.</note>
		/// <param name="position">The position to set.</param>
		/// <param name="orientation">The orientation to set.</param>
		virtual void setTransform(const vec3& position, const quaternion& orientation) = 0;

		/// <summary>
		/// Asynchronously sets linear velocity of the transformable scene element.
		/// </summary>
		/// <param name="linearVelocity">The linear velocity to set.</param>
		virtual void setLinearVelocity(const vec3& linearVelocity) = 0;

		/// <summary>
		/// Asynchronously obtains linear velocity of the transformable scene element.
		/// </summary>
		/// <param name="callback">The callback called with the obtained linear velocity.</param>
		virtual void linearVelocity(GetLinearVelocityCallback callback) = 0;

		/// <summary>
		/// Asynchronously sets angular velocity of the transformable scene element.
		/// </summary>
		/// <param name="angularVelocity">
		/// The angular velocity to set.
		/// The vector direction defines the axis of rotation, and its length defines how fast the rotation is.
		/// </param>
		virtual void setAngularVelocity(const vec3& angularVelocity) = 0;

		/// <summary>
		/// Asynchronously obtains angular velocity of the transformable scene element.
		/// </summary>
		/// <param name="callback">The callback called with the obtained angular velocity.</param>
		virtual void angularVelocity(GetAngularVelocityCallback callback) = 0;

		/// <summary>
		/// Asynchronously sets both the linear and the angular velocities together.
		/// </summary>
		/// <note>This method is faster than setting both velocities independently.</note>
		/// <param name="linearVelocity">The linear velocity to set.</param>
		/// <param name="angularVelocity">The angular velocity to set.</param>
		virtual void setVelocity(const vec3& linearVelocity, const vec3& angularVelocity) = 0;

		// protected construction and destruction methods
	protected:
		virtual ~ITransformable() = default;
	};
}

#endif
