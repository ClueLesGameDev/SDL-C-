#pragma once
#include "SpriteComponent.h"

class BGSpriteComponent : public SpriteComponent
{
public:
	BGSpriteComponent(Actor* owner, int drawOrder = 10); // Bg comes first in painting algorithm so low draw order

	void Update(float dt) override;

	void Draw(SDL_Renderer* renderer) override;

	//Getters and Setters
	void SetBGTexture(const std::vector<SDL_Texture*>& textures);

	void SetScrollSpeed(float speed) { mScrollSpeed = speed; }

	void SetScreenSize(Vector2& size) { mScreenSize = size; }

	float GetScrollSpeed() const { return mScrollSpeed; }

protected:
	
	struct BGTexture
	{
		SDL_Texture* mTexture;
		
		Vector2 mOffeset;
	};

	std::vector<BGTexture*> mBGTextures;
	
	float mScrollSpeed;

	Vector2 mScreenSize;

};

