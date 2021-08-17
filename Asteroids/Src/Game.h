#pragma once
#include<SDL.h>
#include<SDL_image.h>
#include "Actor.h"

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

	SDL_Texture* LoadTex(const char* fileName);

	bool mIsRunning;
	bool mIsUpdatingActors;			//to see wether the actors are getting updated and is iterating.

	SDL_Window*		mWindow;
	SDL_Renderer* mRenderer;

	std::vector<Actor*> mActors;
	std::vector<Actor*> mPendingActors;

	Uint32 mTicksCount;
};

