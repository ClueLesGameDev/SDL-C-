#pragma once
#include "Component.h"

class MoveComponent : public Component
{
	MoveComponent(Actor* owner, int updateOrder = 10);

	virtual void Update(float dt) override;

	//Getters and Setters
	float GetForwardSpeed() const { return mForwardSpeed; }
	void  SetForwardSpeed(float speed) { mForwardSpeed = speed; }

	float GetAngualrSpeed() const { return mAngularSpeed; }
	void  SetAngularSpeed(float speed) { mAngularSpeed = speed; }



protected:
	 
	//Different speed components for forward and angular speed
	float mForwardSpeed;
	float mAngularSpeed;
};


