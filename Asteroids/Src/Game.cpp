#include "Game.h"

Game::Game() : mWindow(NULL), mRenderer(NULL)
{
	
}

Game::~Game()
{
	delete mWindow;
	delete mRenderer;
}

bool Game::Initialize()
{
	if (SDL_Init(SDL_INIT_VIDEO))
	{
		SDL_Log("Unable to initialize SDL : %s", SDL_GetError());

		return false;
	}

	mWindow = SDL_CreateWindow("Asteroid", 100, 30, 1024, 768, 0);

	if (!mWindow)
	{
		SDL_Log("Unable to Create Window! : %s", SDL_GetError());

		return false;
	}

	mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	if (!mRenderer)
	{
		SDL_Log("Unable to Create Renderer! : %s", SDL_GetError());

		return false;
	}

	mIsRunning = true;
	return true;

}

void Game::Run()
{
	while (mIsRunning)
	{
		InputProcess();

		Update();

		GenOutput();
	}
}

void Game::InputProcess()
{
	SDL_Event event;

	//run while an event is in th queue
	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)
		{
			mIsRunning = false;
			break;
		}
	}

	//getting the whole state of keyboard
	const Uint8* state = SDL_GetKeyboardState(NULL);  //pointer to an array of all the keys in the keyboard.

	//indexing through for specific key in the array to see if it is set true(or event is assossiated)

	if (state[SDL_SCANCODE_ESCAPE])
	{
		mIsRunning = false;
	}
}

void Game::Exit()
{
	SDL_DestroyWindow(mWindow);
	SDL_DestroyRenderer(mRenderer);

	SDL_Quit();
}