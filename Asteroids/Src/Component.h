#pragma once
#include <cstdint>

class Component
{
public:
	Component(class Actor* owner, int updateOrder = 100);		// the lower the update order the earlier it will get updated
	
	virtual ~Component();

	virtual void Update(float dt);

	// Process input for this component
	virtual void InputProcess(const uint8_t* keyState) {}

	int GetUpdateOrder() const { return mUpdateOrder;  }

protected:

	class Actor* mOwner;

	int mUpdateOrder;
};
