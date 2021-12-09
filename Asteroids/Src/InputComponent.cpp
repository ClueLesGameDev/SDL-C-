#include "InputComponent.h"

InputComponent::InputComponent(Actor* owner)
	: MoveComponent(owner),
	  mForwardKey(0), mBackwardKey(0),
	  mClockwiseKey(0), mAntiClockwiseKey(0)
{

}

void InputComponent::InputProcess(const uint8_t* keyState)
{
	//Calculating the Forward Speed
	float forwardSpeed = 0.0f;

	if (keyState[mForwardKey])
	{
		forwardSpeed += mMaxForwardSpeed;
	}
	
	if (keyState[mBackwardKey])
	{
		forwardSpeed -= mMaxForwardSpeed;
	}

	SetForwardSpeed(forwardSpeed);

	//Calculating the Angular Speed
	float angularSpeed = 0.0f;

	if (keyState[mClockwiseKey])
	{
		angularSpeed += mMaxAngularSpeed;
	}

	if (keyState[mAntiClockwiseKey])
	{
		angularSpeed -= mMaxAngularSpeed;
	}

	SetAngularSpeed(angularSpeed);
}
