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
};

//------------------------------------------------------------------------------



//2d Vector class---------------------------------------------------

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

	Vector2 operator*(const Vector2& val)
	{
		return { x * val.x, y * val.y };
	}

	//------------------------------------------------------------------

	
	float x = 0;
	float y = 0;
};

//----------------------------------------------------------------------
