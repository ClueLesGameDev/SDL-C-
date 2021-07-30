#include "Game.h"


const int thickness = 15;
int mPaddleDir;
const int paddleH = thickness + 100;

Game::Game() : 
mWindow(NULL), 
mPaddlePos{ thickness + 5,768 / 2 },
mBallVel{ -200.f, 235.f }
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

	mWindow = SDL_CreateWindow("Project1", 100, 30, 1024, 768, 0); //function creates a window and return a pointer to that window
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
	mBallPos = { 1024 / 2,768 / 2 };
	

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

	//adding/subtracting because if pressed to gether pddle shouldnt move.
	if (state[SDL_SCANCODE_W])
	{
		mPaddleDir -= 1;        
	}

	if (state[SDL_SCANCODE_S])
	{
		mPaddleDir += 1;
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


	if (mPaddleDir != 0)
	{
		mPaddlePos.y += mPaddleDir * 300 * deltaTime;

		//Setting boundaries for the paddle.
		if (mPaddlePos.y < (paddleH/2  + thickness))
		{
			mPaddlePos.y = paddleH/2  + thickness;
		}

		if (mPaddlePos.y > 768 - paddleH / 2 - thickness)
		{
			mPaddlePos.y = 768 - paddleH / 2 - thickness;
		}

	}

	mBallPos.x += mBallVel.x * deltaTime;
	mBallPos.y += mBallVel.y * deltaTime;

	if (mBallVel.y < 0.0f && mBallPos.y <= thickness)
	{
		mBallVel.y *= -1;
	}

 
	if (mBallVel.y > 0.0f && mBallPos.y >= (768 - thickness))
	{
		mBallVel.y *= -1;
	}
	
	float diff =  mPaddlePos.y - mBallPos.y;
	
	//calculating the absoulte value
	diff = (diff > 0.0f) ? diff : -diff;

	if (diff <= paddleH  && mBallPos.x <= 25.f && mBallPos.x >= 20.f && mBallVel.x < 0.f)
	{
		mBallVel.x *= -1.0f;
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
	
	//SDL_Rect leftWall{ 0,0,thickness,768 };
	//SDL_RenderFillRect(mRenderer, &leftWall);
	
	SDL_Rect rightWall{ 1024 - thickness,0,thickness,768 };
	SDL_RenderFillRect(mRenderer, &rightWall);

	//paddle
	SDL_Rect paddle
	{
		static_cast<int>(mPaddlePos.x - thickness / 2),
		static_cast<int>(mPaddlePos.y - thickness / 2),
		thickness,
		paddleH
	};
	SDL_RenderFillRect(mRenderer, &paddle);

	//Ball
	SDL_Rect ball
	{
		static_cast<int>(mBallPos.x - thickness / 2),
		static_cast<int>(mBallPos.y - thickness / 2),
		thickness,
		thickness
	};
	SDL_RenderFillRect(mRenderer, &ball);

	
	//swapping the buffer so the screen can display the renderer
	SDL_RenderPresent(mRenderer);


}
