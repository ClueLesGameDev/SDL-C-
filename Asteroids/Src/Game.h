#pragma once
#include<SDL.h>
#include<SDL_image.h>
#include<unordered_map>

#include"Actor.h"
#include"SpriteComponent.h"


class Game
{
public:
	Game();
	~Game();

	bool Initialize();
	void Run();
	void Exit();

protected:

	void InputProcess();
	void Update();
	void GenOutput() {};

	void AddActor(Actor* actor);
	void RemoveActor(Actor* actor) {};

	void AddSprite(SpriteComponent* sprite);
	void RemoveSprite(SpriteComponent* sprite) {};

	SDL_Texture* GenerateTex(const std::string& fileName);

	bool mIsRunning;
	bool mIsUpdatingActors;			//to see wether the actors are getting updated and is iterating.

	SDL_Window*		mWindow;
	SDL_Renderer* mRenderer;

	std::vector<Actor*> mActors;
	std::vector<Actor*> mPendingActors;

	std::vector<SpriteComponent*> mSprites;

	std::unordered_map<std::string, SDL_Texture*> mTextures;

	Uint32 mTicksCount;
};

