#include "MoveComponent.h"

void MoveComponent::Update(float dt)
{
	//checking if angular speed is near to zero then no need to update
	if (!Math::NearZero(mAngularSpeed))
	{
		float rot = mOwner->GetRoation();

		rot += mAngularSpeed * dt;

		mOwner->SetRoation(rot);
	}

	//checking if forward speed is near to zero then no need to update
	if (!Math::NearZero(mForwardSpeed))
	{
		Vector2 pos = mOwner->GetPosition();

		pos = pos + mOwner->GetForward() * mForwardSpeed * dt;

		//wrapping the screen when off bounds assuming the window is 1024 x 768
		if (pos.x < 0.0f)
		{
			pos.x = 1022.0f; 
		}
		else if (pos.x > 1024.0f) 
		{
			pos.x = 2.0f;
		}

		if (pos.y < 0.0f)
		{
			pos.y = 766.0f;
		}
		else if (pos.y > 768.0f) 
		{
			pos.y = 2.0f;
		}

		mOwner->SetPosition(pos);
	}
	
}
