#include "BGSpriteComponent.h"


// setting each bg texture to the right of the previous one so as to get the moving effect while scrolling
void BGSpriteComponent::SetBGTexture(const std::vector<SDL_Texture*>& textures)
{
	int count = 0;

	for (auto tex : textures)
	{
		BGTexture temp;

		temp.mTexture = tex;

		temp.mOffeset.x = count * mScreenSize.x;
		temp.mOffeset.y = 0;

		mBGTextures.emplace_back(temp);

		count++;
	}
}


void BGSpriteComponent::Update(float dt)
{
	SpriteComponent::Update(dt);

	for (auto& bg : mBGTextures)
	{
		bg->mOffeset.x += mScrollSpeed * dt;

		//if the image is completly out of the screen reset it to the righ of the last bg texure (infinite scrolling)
		if (bg->mOffeset.x < -mScreenSize.x)
		{
			bg->mOffeset.x = (mBGTextures.size() - 1) * mScreenSize.x - 1;
		}
	}
}

void BGSpriteComponent::Draw(SDL_Renderer* renderer)
{
}
