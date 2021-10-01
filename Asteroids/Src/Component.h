#pragma once
#include "Actor.h"

class Component
{
public:
	Component(class Actor* owner, int updateOrder = 100);		// the lower the update order the earlier it will get updated
	
	virtual ~Component();

	virtual void Update(float dt);

	int GetUpdateOrder() const { return mUpdateOrder;  }

protected:

	Actor* mOwner;

	int mUpdateOrder;
};
