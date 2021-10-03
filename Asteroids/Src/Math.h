#pragma once
#include <cmath>


//General Math Functions-----------------------------------------------------

namespace Math
{
	const float pi = 3.1415926535f;

	inline float ToRad(float degrees)
	{
		return degrees * pi / 180.0f;
	}

	inline float ToDeg(float radians)
	{
		return radians * 180.0f / pi;
	}

	inline float Sqrt(float val)
	{
		return sqrtf(val);
	}

	inline 
};

//------------------------------------------------------------------------------



//2D Vector class---------------------------------------------------

class Vector2 
{
public:
	//Basic vector operations---------------------------------------
	
	Vector2 operator+(const Vector2& val)
	{
	
		return { x + val.x, y + val.y };
	}

	Vector2 operator-(const Vector2& val)
	{
		return { x - val.x, y - val.y };
	}

	//Scalar multiplication
	Vector2 operator*(const float val)
	{
		return { x * val, y * val };
	}

	//------------------------------------------------------------------

	float LengthSqr()
	{
		return (x * x + y * y);
	}

	float Length()
	{
		return (Math::Sqrt(LengthSqr()));
	}

	//normalizing the vector erasing the magnitude
	void Normalize()
	{
		x /= Length();
		y /= Length();
	}
	
	//static function returning the normalized value without changing the actual vectors
	static Vector2 Normalize(const Vector2& val)
	{
		Vector2 temp = val;
		temp.Normalize();
		return temp;
	}
	
	float x = 0;
	float y = 0;
};

//----------------------------------------------------------------------

//3D  Vector Class----------------------------------------------------------

class Vector3
{
public:

	//Basic vector operations
	Vector3 operator+(const Vector3& val)
	{
		return { x + val.x, y + val.y, z + val.z };
	}

	Vector3 operator-(const Vector3& val)
	{
		return { x - val.x, y - val.y, z - val.z };
	}

	//Scalar multiplicaton
	Vector3 operator*(const float val)
	{
		return { x * val, y * val, z * val };
	}

	float x = 0; 
	float y = 0;
	float z = 0;
};