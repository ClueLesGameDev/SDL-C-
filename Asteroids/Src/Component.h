#pragma once

class Componenent
{
public:
	Componenent(class Actor* owner, int updateOrder = 100);		// the lower the update order the earlier it will get updated
	virtual ~Componenent();

	virtual void Update(float dt);

	int GetUpdateOrder() const { return mUpdateOrder;  }

protected:

	class Actor* mOwner;

	int mUpdateOrder;
};
