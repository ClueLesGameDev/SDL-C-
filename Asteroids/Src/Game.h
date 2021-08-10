#pragma once
#include<SDL.h>

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
	void Update() {};
	void GenOutput() {};

	bool mIsRunning;

	SDL_Window*		mWindow;
	SDL_Renderer* mRenderer;
};

