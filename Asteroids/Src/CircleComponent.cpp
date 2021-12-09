#include "CircleComponent.h"
#include "Actor.h"

CircleComponent::CircleComponent(Actor* owner)
	: Component(owner), mRadius(0.0f)
{

}

float CircleComponent::GetRadius() const
{
	return mOwner->GetScale() * mRadius;
}

const Vector2& CircleComponent::GetCenter() const
{
	return mOwner->GetPosition();
}

bool Intersect(const CircleComponent& a, const CircleComponent& b)
{
	Vector2 difference = a.GetCenter() - b.GetCenter();
	float distSq = difference.LengthSqr();

	float radiusSumSq = a.GetRadius() + b.GetRadius();
	radiusSumSq *= radiusSumSq;

	return distSq <= radiusSumSq;
}
