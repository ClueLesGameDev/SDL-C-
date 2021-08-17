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

	if (IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG) == 0)
	{
		SDL_Log("Unable to initilaise the SDL_Image! : %s", SDL_GetError());
		return false;
	}
		
	mIsRunning = true;
	mIsUpdatingActors = false;

	mTicksCount = 0;

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

void Game::Update()
{
	//Calculating deltatime

	//frame limiting
	while (!SDL_TICKS_PASSED(SDL_GetTicks(), mTicksCount + 16));

	float deltaTime = (SDL_GetTicks() - mTicksCount) / 1000;

	//clamping deltaTime
	if (deltaTime > .05f)
	{
		deltaTime = .05f;
	}

	mTicksCount = SDL_GetTicks();

	//updating GameObjects
	mIsUpdatingActors = true;

	for (auto actor : mActors)
	{
		actor->Update(deltaTime);
	}

	mIsUpdatingActors = false;

	//moving pending actors to the main list
	for (auto pending : mPendingActors)
	{
		mActors.emplace_back(pending);
	}

	mPendingActors.clear();

	//checking if there are dead GameObjects and sending them to the temporarylist
	std::vector<Actor*> deadActors;
	
	for (auto actor : mActors)
	{
		if (actor->Getstate() == Actor::EDead)
		{
			deadActors.emplace_back(mActors);
		}
	}

	//deleting all the dead GameObjetcs
	for (auto actor : deadActors)
	{
		delete actor;
	}
}

void Game::Exit()
{
	//deleting the remianing actors on the list
	while (!mActors.empty())
	{
		delete mActors.back();
	}
	SDL_DestroyWindow(mWindow);
	SDL_DestroyRenderer(mRenderer);

	SDL_Quit();
}

void Game::AddActor(Actor* actor)
{
	if (mIsUpdatingActors)
	{
		//temporarily placed in pendingactors till all the actors on the list are updated.
		mPendingActors.emplace_back(actor);
	}
	else
	{
		//acotrs are not updated at the moment so can be directly placed in to the list
		mActors.emplace_back(actor);
	}
}

//encapsulating loading texture from surface into a single function
SDL_Texture* Game::LoadTex(const char* fileName)
{
	SDL_Surface* surface = IMG_Load(fileName);
	
	if (!surface)
	{
		SDL_Log("Couldn't load texture : %s", fileName);
		return nullptr;
	}

	//creating texture from surface
	SDL_Texture* tex = SDL_CreateTextureFromSurface(mRenderer, surface);
	SDL_FreeSurface(surface);

	if (!tex)
	{
		SDL_Log("Couldnt convert texture from surface : %s", fileName);
		return nullptr;
	}

	return tex;
}