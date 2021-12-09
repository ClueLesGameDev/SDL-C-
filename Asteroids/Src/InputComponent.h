#pragma once
#include "MoveComponent.h"

class InputComponent : public MoveComponent
{
public:

	InputComponent(class Actor* owner);

	void InputProcess(const uint8_t* keyState) override;

	//Getters and Setters
	float GetForwardSpeed() const { return mMaxForwardSpeed; }
	float GetAngularSpeed() const { return mMaxAngularSpeed; }

	void SetForwardSpeed(float forwardSpeed) { mForwardSpeed = forwardSpeed; }
	void SetForwardSpeed(float angularSpeed) { mAngularSpeed = angularSpeed; }

private:

	//Forward and Angular Speed
	float mMaxForwardSpeed;
	float mMaxAngularSpeed;

	//Forward and Angular Movement Inputs

	int mForwardKey;
	int mBackwardKey;

	int mClockwiseKey;
	int mAntiClockwiseKey;

};

