#include "SpriteComponent.h"
#include "Actor.h"
#include "SDL_image.h"
#include "Game.h"


SpriteComponent::SpriteComponent(Actor* owner, int drawOrder)
	:Component(owner)
	, mTexture(nullptr)
	, mDrawOrder(drawOrder)
	, mTexWidth(0)
	, mTexHeight(0)
{
	mOwner->GetGame()->AddSprite(this);
}

SpriteComponent::~SpriteComponent()
{
	mOwner->GetGame()->RemoveSprite(this);
}

void SpriteComponent::SetTexture(SDL_Texture* texture)
{
	mTexture = texture;

	//Get the width and hieght of the texture
	SDL_QueryTexture(texture, nullptr, nullptr, &mTexWidth, &mTexWidth);

}

void SpriteComponent::Draw(SDL_Renderer* renderer)
{
	if (mTexture)
	{
		SDL_Rect r;

		//Scaling the width and height of the sprite according to the owners scale
		r.w = static_cast<int>(mTexWidth * mOwner->GetScale());
		r.h = static_cast<int>(mTexHeight * mOwner->GetScale());

		//centering the rect with respect to the gameobjects positions
		r.x = static_cast<int>(mOwner->GetPosition().x - r.w / 2);
		r.y = static_cast<int>(mOwner->GetPosition().y - r.h / 2);

		SDL_RenderCopyEx(renderer, mTexture, nullptr, &r, -Math::ToDeg(mOwner->GetRoation()), nullptr, SDL_FLIP_NONE);
	}
}
