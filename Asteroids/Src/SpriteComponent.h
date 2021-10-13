#pragma once
#include "Component.h"


class SpriteComponent : public Component
{
public:

	SpriteComponent(Actor* owner, int drawOrder = 100);		//drawOrder to implement painters algorithm
	~SpriteComponent();

	//Getters and Setters
	virtual void SetTexture(SDL_Texture* texture);

	virtual void Draw(SDL_Renderer* renderer);

	int GetDrawOrder() const { return mDrawOrder; }
	int GetTexHeight() const { return mTexHeight; }
	int GetTexWidth() const { return mTexWidth; }

protected:

	SDL_Texture* mTexture;

	int mDrawOrder;
	int mTexHeight;
	int mTexWidth;
}; 