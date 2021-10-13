#include "Actor.h"

Vector2 Actor::GetForward() const
{
	{
		//SDL graphics use +ve y axis through downward direction use negative axis
		return Vector2{ Math::Cos(mRotation), -Math::Sin(mRotation) };
	}
}
