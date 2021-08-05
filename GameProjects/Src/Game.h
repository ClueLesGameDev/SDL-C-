#pragma once
#include <SDL.h>
#include<vector>

struct Vector2
{
	float x;
	float y;
};

struct Ball
{
	Vector2 BallPos;
	Vector2 BallVel;
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
	Vector2 mPaddle_2_Pos;
	
	std::vector<Ball*> mBalls;
	

	Uint32 mTicksCount;

};
