#include "Random.h"

void Random::Init()
{
	std::random_device rd;
	Random::Seed(rd());
}

void Random::Seed(unsigned int seed)
{
	sGen.seed(seed);
}

float Random::GetRandomFloat()
{
	return GetRandomRangeFloat(0.0f, 1.0f);
}

float Random::GetRandomRangeFloat(float min, float max)
{
	std::uniform_real_distribution<float> dist(min, max);
	return dist(sGen);
}

int Random::GetRandomRangeInt(int min, int max)
{
	std::uniform_real_distribution<int> dist(min, max);
	return dist(sGen);
}

Vector2 Random::GetRandomRangeVector(Vector2& min, Vector2& max)
{
	Vector2 r = { GetRandomFloat(), GetRandomFloat() };
	return min + (max - min) * r;
}

Vector3 Random::GetRandomRangeVector(Vector3& min, Vector3& max)
{
	Vector3 r = { GetRandomFloat(), GetRandomFloat(), GetRandomFloat() };
	return min + (max - min) * r;
}

