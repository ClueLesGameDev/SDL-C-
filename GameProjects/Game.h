#pragma once
#include <SDL.h>

struct Vector2
{
	float x;
	float y;
};

class Game
{
public:

	Game();
	~Game() { delete mWindow; }

	bool Initialize();
	void Run();
	void Exit();

	

private:

	void InputProcess();
	void UpdateGame();
	void OutputGen();

	SDL_Window* mWindow;
	SDL_Renderer* mRenderer;

	bool mIsRunning;

	Vector2 mPaddlePos;
	Vector2 mBallPos;
	Vector2 mBallVel;
	

	Uint32 mTicksCount;

};
