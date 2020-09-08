///
/// \author Szymon Palka <szymon.palka@techmo.pl>
/// \date 01.01.2017-26.05.2017
///
#ifndef STK__MATH__H
#define STK__MATH__H

#include <ostream>

namespace stk
{
	struct vec3
	{

		// public construction methods
	public:

		vec3(float x = 0.0f, float y = 0.0f, float z = 0.0f)
			: x{ x }, y{ y }, z{ z }
		{
		}

		// public values
	public:

		float x;
		float y;
		float z;

	};

	struct vec4
	{

		// public construction methods
	public:

		vec4(float x = 0.0f, float y = 0.0f, float z = 0.0f, float w = 0.0f)
			: x{ x }, y{ y }, z{ z }, w{ w }
		{
		}

		// public values
	public:

		float x;
		float y;
		float z;
		float w;

	};

	struct quaternion
	{

		//public construction methods
	public:

		quaternion(float w = 1.0f, float x = 0.0f, float y = 0.0f, float z = 0.0f)
			: w{ w }, x{ x }, y{ y }, z{ z }
		{
		}

		//public values
	public:

		float w;
		float x;
		float y;
		float z;

	};

	struct face
	{
		vec3 a;
		vec3 b;
		vec3 c;

		face(const vec3& inA = vec3{}, const vec3& inB = vec3{}, const vec3& inC = vec3{})
			: a{ inA }
			, b{ inB }
			, c{ inC }
		{
		}

		vec3& operator[](size_t index)
		{
			return *(&a + index);
		}

		const vec3& operator[](size_t index) const
		{
			return *(&a + index);
		}
	};

	using Direction = vec3;
	using Rotation = quaternion;

	inline bool operator==(const vec3& lhv, const vec3& rhv)
	{
		return (lhv.x == rhv.x && lhv.y == rhv.y && lhv.z == rhv.z);
	}

	inline bool operator!=(const vec3& lhv, const vec3& rhv)
	{
		return !(lhv == rhv);
	}

	inline bool operator==(const quaternion& lhv, const quaternion& rhv)
	{
		return (lhv.w == rhv.w && lhv.x == rhv.x && lhv.y == rhv.y && lhv.z == rhv.z);
	}

	inline bool operator!=(const quaternion& lhv, const quaternion& rhv)
	{
		return !(lhv == rhv);
	}
}

/// <summary>
/// Writes the vector v=[x,y,z] to the output stream in form: [x, y, z].
/// </summary>
/// <param name="output">Output stream, in which the vector should be placed.</param>
/// <param name="v">Vector, which should be written to the output stream.</param>
/// <returns>Given output stream.</returns>
inline std::ostream& operator<<(std::ostream& output, const stk::vec3& v)
{
	output << "[" << v.x << ", " << v.y << ", " << v.z << "]";
	return output;
}

#endif
