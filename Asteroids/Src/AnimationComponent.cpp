#include "AnimationComponent.h"


void AnimationComponent::SetAnimTexture(const std::vector<SDL_Texture*>& texture)
{
	mAnimTextures = texture;

	//if there is textures in the animation set currframe to 0 and current texture to the first one
	if (mAnimTextures.size() > 0)
	{
		mCurrentFrame = 0;
		SetTexture(mAnimTextures[0]);
	}
	
}

void AnimationComponent::Update(float dt)
{
	SpriteComponent::Update(dt);

	if (mAnimTextures.size() > 0)
	{
		mCurrentFrame += mAnimFps * dt;

		//wrapping the frame if exceeded size

		while (mCurrentFrame >= mAnimTextures.size())
		{
			mCurrentFrame -= mAnimTextures.size();
		}

		SetTexture(mAnimTextures[static_cast<int>(mCurrentFrame)]);
	}
}
