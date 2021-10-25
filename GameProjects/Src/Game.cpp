#include "Game.h"
#include <iostream>

const int thickness = 15;
int mPaddleDir;
int mPaddle_2_Dir;
const int paddleH = thickness + 100;

Game::Game() : 
mWindow(NULL), 
mPaddlePos{ thickness ,768 / 2 },
mPaddle_2_Pos{1024 - thickness,768/2}
{
	mIsRunning = true;
	mTicksCount = 0;
}

bool Game::Initialize()
{
	if (SDL_Init(SDL_INIT_VIDEO))
	{
		SDL_Log("Unable to initialize SDL : %s", SDL_GetError());
		
		return false;
	}

	mWindow = SDL_CreateWindow("PingPong", 100, 30, 1024, 768, 0); //function creates a window and return a pointer to that window
	if (!mWindow)
	{
		SDL_Log("Failed to create window : %s", SDL_GetError());

		return false;
	}

	mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC); //function creates a renderer and return a pointer to that renderer
	if (!mRenderer)
	{
		SDL_Log("FAiled to create Renderer : %s", SDL_GetError());

		return false;
	}
	
	//multiple mBalls
	for (int i = 0; i < 2; i++)
	{
		Ball* b = new Ball();
		mBalls.push_back(b);
	}

	mBalls[0]->BallPos = { 1024 / 2,768 / 2 };
	mBalls[0]->BallVel = { -200.f, 235.f };

	mBalls[1]->BallPos = { 1024 / 2,768 / 2 };
	mBalls[1]->BallVel = { 200.f, -235.f };
	

	return true;
}

void Game::Run()
{ 
	while (mIsRunning)
	{
		InputProcess();
		
		UpdateGame();

		OutputGen();
	}
}

void Game::Exit()
{
	SDL_DestroyWindow(mWindow);
	SDL_DestroyRenderer(mRenderer);

	SDL_Quit();
}

void Game::InputProcess()
{
	SDL_Event event;

	while (SDL_PollEvent(&event)) //sdl_pollevent takes a pointer to an sdl event which is the sddress of "event" variable.
	{
		//returns true if there is an event in the queue

		switch (event.type)
		{
			case SDL_QUIT:
				
				mIsRunning = false;
				break;
		}
	}

	//getting the whole state of keyboard

	const Uint8* state = SDL_GetKeyboardState(NULL);  //pointer to an array of all the keys in the key board.

	//indexing through for specific key in the array to see if it is set true(or event is assossiated)

	if (state[SDL_SCANCODE_ESCAPE])
	{
		mIsRunning = false;
	}

	mPaddleDir = 0;
	mPaddle_2_Dir = 0;

	//adding/subtracting because if pressed to gether pddle shouldnt move.
	if (state[SDL_SCANCODE_W])
	{
		mPaddleDir -= 1;        
	}

	if (state[SDL_SCANCODE_S])
	{
		mPaddleDir += 1;
	}

	//paddle2 directions
	if (state[SDL_SCANCODE_I])
	{
		mPaddle_2_Dir -= 1;
	}

	if (state[SDL_SCANCODE_K])
	{
		mPaddle_2_Dir += 1;
	}
	
}

void Game::UpdateGame()
{
	//frame limiting so that the frame will wait for an additional 1.6ms before jumping to next frmae
	while (!SDL_TICKS_PASSED(SDL_GetTicks(), mTicksCount + 16));

	//SDL_GetTicks gives time elapsed(in millisecond) from the time SDL_Init() is called
	float deltaTime = (SDL_GetTicks() - mTicksCount) / 1000.f;		//converted to seconds

		//clamping the deltatime
	if (deltaTime > .05f)
	{
		deltaTime = .05f;
	}


	//updating mTicks count so that in next iteration it is total time elapsd - time elapsed during previous frames = time per one frame.
	mTicksCount = SDL_GetTicks();


	if (mPaddleDir != 0 || mPaddle_2_Dir !=0)
	{
		mPaddlePos.y += mPaddleDir * 300 * deltaTime;
		mPaddle_2_Pos.y += mPaddle_2_Dir * 300 * deltaTime;

		//Setting boundaries for the paddle.
		if (mPaddlePos.y < thickness)
		{
			mPaddlePos.y = thickness;
		}

		if (mPaddlePos.y > 768 - (paddleH + thickness))
		{
			mPaddlePos.y = 768 - (paddleH + thickness);
		}

		//Setting boundaries for paddle2
		if (mPaddle_2_Pos.y < thickness)
		{
			mPaddle_2_Pos.y = thickness;
		}

		if (mPaddle_2_Pos.y > 768 - (paddleH + thickness))
		{
			mPaddle_2_Pos.y = 768 - (paddleH + thickness);
		}

	}
	
	for (int i = 0; i < mBalls.size(); i++)
	{
		mBalls[i]->BallPos.x += mBalls[i]->BallVel.x * deltaTime;
		mBalls[i]->BallPos.y += mBalls[i]->BallVel.y * deltaTime;

		if (mBalls[i]->BallVel.y < 0.0f && mBalls[i]->BallPos.y <= thickness)
		{
			mBalls[i]->BallVel.y *= -1;
		}


		if (mBalls[i]->BallVel.y > 0.0f && mBalls[i]->BallPos.y >= (768 - thickness))
		{
			mBalls[i]->BallVel.y *= -1;
		}

		float diff = mPaddlePos.y - mBalls[i]->BallPos.y;
		float diff2 = mPaddle_2_Pos.y - mBalls[i]->BallPos.y;

		//calculating the absoulte value
		diff = (diff > 0.0f) ? diff : -diff;
		diff2 = (diff2 > 0.0f) ? diff2 : -diff2;

		//ball hitting paddle
		if (diff <= paddleH && mBalls[i]->BallPos.x < (mPaddlePos.x + thickness / 2) && mBalls[i]->BallPos.x > thickness/2 )
		{
			mBalls[i]->BallVel.x *= -1.0f;
			mBalls[i]->BallVel.y = mBalls[i]->BallVel.y + mPaddlePos.y / 100;
		}


		//ball hiting paddle2
		if (diff2 <= paddleH && mBalls[i]->BallPos.x > 1024 - (mPaddlePos.x + thickness / 2) && mBalls[i]->BallPos.x < (1024 - thickness / 2))
		{
			mBalls[i]->BallVel.x *= -1.0f;
			mBalls[i]->BallVel.y += (mBalls[i]->BallVel.y - mPaddle_2_Pos.y) / 100;
		}

	}

	

}

void Game::OutputGen()
{
	//setting a colour to renderer
	SDL_SetRenderDrawColor(mRenderer ,0, 0, 255, 255);

	//clearng the current renderer with the set colour
	SDL_RenderClear(mRenderer);

	SDL_SetRenderDrawColor(mRenderer, 255, 255, 255, 255); //setting the color to white for the rectangle
	
	//struct typedef to SDL_Rect with 4 int parameters and object name STL_Rect => SDL_Rect wall = struct with 4 int parametrs and an object named wall
	SDL_Rect topWall{ 0,0,1024,thickness };
	SDL_RenderFillRect(mRenderer, &topWall); //const because if changed inside the function it will also change the original wall as it is passed as ref using a pointer
	
	SDL_Rect bottomWall{ 0,768 - thickness,1024,thickness };
	SDL_RenderFillRect(mRenderer, &bottomWall);
	

	//paddle
	SDL_Rect paddle
	{
		static_cast<int>(mPaddlePos.x - thickness / 2),
		static_cast<int>(mPaddlePos.y - thickness / 2),
		thickness,
		paddleH
	};
	SDL_RenderFillRect(mRenderer, &paddle);

	SDL_Rect paddle_2
	{
		static_cast<int>(mPaddle_2_Pos.x - thickness / 2),
		static_cast<int>(mPaddle_2_Pos.y - thickness / 2),
		thickness,
		paddleH
	};
	SDL_RenderFillRect(mRenderer, &paddle_2);

	//Balls
	for (int i = 0; i < mBalls.size(); i++)
	{
		SDL_Rect ball
		{
			static_cast<int>(mBalls[i]->BallPos.x - thickness / 2),
			static_cast<int>(mBalls[i]->BallPos.y - thickness / 2),
			thickness,
			thickness
		};
		SDL_RenderFillRect(mRenderer, &ball);
	}
	

	
	//swapping the buffer so the screen can display the renderer
	SDL_RenderPresent(mRenderer);


}
