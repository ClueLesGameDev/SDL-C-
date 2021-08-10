#pragma once
class Math
{
};


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
