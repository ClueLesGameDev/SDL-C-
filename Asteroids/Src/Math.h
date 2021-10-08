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

	inline float Cos(float angle)
	{
		return cosf(angle);
	}

	inline float Sin(float angle)
	{
		return sinf(angle);

	}

	inline float Atan2(float y, float x)
	{
		return atan2f(y, x);
	}

	inline float Acos2(float val)
	{
		return acosf(val);
	}
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

	static float Dot(const Vector2& a, const Vector2& b)
	{
		return ((a.x * b.x) + (a.y * b.y));
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

	float LengthSqr()
	{
		return (x * x + y * y + z * z);
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
		z /= Length();
	}

	//static function returning the normalized value without changing the actual vectors
	static Vector3 Normalize(const Vector3& val)
	{
		Vector3 temp = val;
		temp.Normalize();
		return temp;
	}

	static float Dot(const Vector3& a, const Vector3& b)
	{
		return ((a.x * b.x) + (a.y * b.y) + (a.z * b.z));
	}

	static Vector3 Cross(const Vector3& a, const Vector3& b)
	{
		Vector3 temp;
		temp.x = ((a.y * b.z) - (a.z * b.y));
		temp.y = ((a.z * b.x) - (a.x * b.z));
		temp.z = ((a.x * b.y) - (a.y * b.z));
		return temp;
	}

	float x = 0; 
	float y = 0;
	float z = 0;
};