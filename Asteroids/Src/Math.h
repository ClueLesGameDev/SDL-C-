#pragma once
#include <cmath>
#include <limits>


//General Math Functions-----------------------------------------------------

namespace Math
{
	const float pi = 3.1415926535f;
	const float infinity = std::numeric_limits<float>::infinity();
	const float negInfinity = -std::numeric_limits<float>::infinity();

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

	inline bool NearZero(float val, float epsilon = .001f)		// to check a val is near to zero
	{
		if (val <= epsilon)
		{
			return true;
		}
		
		else
		{
			return false;
		}
			
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

	Vector2() : x(0.0f), y(0.0f) {};

	explicit Vector2(float inX, float inY) : x(inX), y(inY) {};

	void Set(float inX, float inY)
	{
		x = inX;
		y = inY;
	}

	/*------------------------------------------------------------------
	//Basic vector operations - Static
	------------------------------------------------------------------*/
	
	//Vector Addition
	friend Vector2 operator+(const Vector2& valA, const Vector2& valB)
	{
	
		return Vector2(valA.x + valB.x, valA.y + valB.y);
	}

	//Vector Subtraction
	friend Vector2 operator-(const Vector2& valA, const Vector2& valB)
	{
		return Vector2( valA.x - valB.x, valA.y - valB.y);
	}

	//Scalar multiplication Vector * Float
	friend Vector2 operator*(const Vector2& valA, const float valF)
	{
		return Vector2( valA.x * valF, valA.y * valF);
	}

	//Scalar multiplication Float * Vector
	friend Vector2 operator*(const float valF, const Vector2& valA)
	{
		return Vector2( valA.x * valF, valA.y * valF );
	}

	//Component-wise multiplication
	friend Vector2 operator*(Vector2& valA, Vector2& valB)
	{
		return Vector2( valA.x * valB.x, valA.y * valB.y );
	}

	/*------------------------------------------------------------------
	//Basic vector operations - Object
	------------------------------------------------------------------*/

	//Vector Addition
	Vector2 operator+(const Vector2& val)
	{

		return Vector2( x + val.x, y + val.y );
	}

	//Vector Subtraction
	Vector2 operator-(const Vector2& val)
	{
		return Vector2( x - val.x, y - val.y );
	}

	//Scalar multiplication Vector * Float
	Vector2 operator*(const float val)
	{
		return Vector2( x * val, y * val );
	}

	//Component-wise multiplication
	Vector2 operator*(Vector2& val)
	{
		return Vector2( x * val.x, y * val.y );
	}

	/*--------

	---------*/


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

	//Specific static functions
	static const Vector2 zero;
	static const Vector2 unityX;
	static const Vector2 unityY;
	static const Vector2 negUnityX;
	static const Vector2 negUnityY;

	float x, y;
};

//----------------------------------------------------------------------

/*--------

---------*/

//3D  Vector Class----------------------------------------------------------

class Vector3
{
public:

	Vector3() : x(0.0f), y(0.0f), z(0.0f) {};

	explicit Vector3(float inX, float inY, float inZ) : x(inX), y(inY), z(inZ) {};

	void Set(float inX, float inY, float inZ)
	{
		x = inX;
		y = inY;
		z = inZ;
	}
/*------------------------------------------------------------------
//Basic vector operations - Static
------------------------------------------------------------------*/

	//Vector Addition
	friend Vector3 operator+(const Vector3& valA, const Vector3& valB)
	{

		return Vector3( valA.x + valB.x, valA.y + valB.y, valA.z + valB.z );
	}

	//Vector Subtraction
	friend Vector3 operator-(const Vector3& valA, const Vector3& valB)
	{
		return Vector3( valA.x - valB.x, valA.y - valB.y, valA.z - valB.z );
	}

	//Scalar multiplication Vector * Float
	friend Vector3 operator*(const Vector3& valA, const float valF)
	{
		return Vector3( valA.x * valF, valA.y * valF, valA.z * valF );
	}

	//Scalar multiplication Float * Vector
	friend Vector3 operator*(const float valF, const Vector3& valA)
	{
		return Vector3( valA.x * valF, valA.y * valF, valA.z * valF );
	}

	//Component-wise multiplication
	friend Vector3 operator*(Vector3& valA, Vector3& valB)
	{
		return Vector3( valA.x * valB.x, valA.y * valB.y, valA.z * valB.z );
	}

	/*------------------------------------------------------------------
	//Basic vector operations - Object
	------------------------------------------------------------------*/

	//Vector Addition
	Vector3 operator+(const Vector3& val)
	{

		return Vector3( x + val.x, y + val.y, z + val.z );
	}

	//Vector Subtraction
	Vector3 operator-(const Vector3& val)
	{
		return Vector3( x - val.x, y - val.y, z - val.z );
	}

	//Scalar multiplication Vector * Float
	Vector3 operator*(const float val)
	{
		return Vector3( x * val, y * val, z * val );
	}

	//Component-wise multiplication
	Vector3 operator*(Vector3& val)
	{
		return Vector3( x * val.x, y * val.y, z * val.z );
	}

	/*--------
	
	---------*/

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

	//Specific static functions
	static const Vector3 zero;
	static const Vector3 unityX;
	static const Vector3 unityY;
	static const Vector3 unityZ;
	static const Vector3 negUnityX;
	static const Vector3 negUnityY;
	static const Vector3 negUnityZ;
	static const Vector3 infinty;
	static const Vector3 negInfinty;

	float x, y, z;
};