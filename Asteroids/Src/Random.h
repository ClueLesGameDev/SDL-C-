#pragma once

#include <random>
#include "Math.h"

class Random
{
public:

	//initializing
	static void Init();

	//Seed the generator with the specified int. (not used manually)
	static void Seed(unsigned int seed);//?

	//Get a random float b/w 0.0f and 1.0f
	static float GetRandomFloat();

	//Get a random float b/w a certain range
	static float GetRandomRangeFloat(float& min, float& max);

	//Get a random int b/w a certain range
	static int GetRandomRangeInt(int& min, int& max);

	//Get a random vector b/w a certain range
	static Vector2 GetRandomRangeVector(Vector2& min, Vector2& max);
	static Vector3 GetRandomRangeVector(Vector3& min, Vector3& max);


};