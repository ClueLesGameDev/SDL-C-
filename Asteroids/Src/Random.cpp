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
	std::uniform_int_distribution<int> dist(min, max);
	return dist(sGen);
}

Vector2 Random::GetRandomRangeVector(const Vector2& min, const Vector2& max)
{
	Vector2 r = Vector2( GetRandomFloat(), GetRandomFloat() );
	return min + (max - min) * r;
}

Vector3 Random::GetRandomRangeVector(const Vector3& min, const Vector3& max)
{
	Vector3 r = Vector3( GetRandomFloat(), GetRandomFloat(), GetRandomFloat() );
	return min + (max - min) * r;
}

std::mt19937 Random::sGen;