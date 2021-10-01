#pragma once
#include "SpriteComponent.h"


class AnimationComponent : public SpriteComponent
{
public:

	AnimationComponent(class Actor* owner, int drawOrder = 100);

	void Update(float dt) override;  //updating the sprite everry frame for animation

	//Getters and Setters

	void SetAnimTexture(const std::vector<SDL_Texture*>& texture); // passing the vector with pointers to texture by reference

	void SetFPS(float fps) { mAnimFps = fps; }	//setting the current animation speed by altering the fps value

	float GetFPS() const { return mAnimFps; }  //return the current frame rate of the animation

protected:
	
	//can alter the value to increse the speed of the animation
	float mAnimFps;

	float mCurrentFrame;  // the current frme - 0 being the first one

	//storing all the sprites for the animation
	std::vector<SDL_Texture*> mAnimTextures;

};

