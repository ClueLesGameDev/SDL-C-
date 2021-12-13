#include <algorithm>
#include "SDL_image.h"
#include "Game.h"
#include "Actor.h"
#include "Asteroid.h"
#include "SpriteComponent.h"
#include "Random.h"

Game::Game()
	: mWindow(nullptr), mRenderer(nullptr),
	mIsRunning(true), mIsUpdatingActors(false)
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
	Random::Init();

	LoadData();

	mTicksCount = SDL_GetTicks();

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
	const Uint8* keyState = SDL_GetKeyboardState(NULL);  //pointer to an array of all the keys in the keyboard.

	//indexing through for specific key in the array to see if it is set true(or event is assossiated)

	if (keyState[SDL_SCANCODE_ESCAPE])
	{
		mIsRunning = false;
	}

	mIsUpdatingActors = true;

	for (auto actor : mActors)
	{
		actor->InputProcess(keyState);
	}

	mIsUpdatingActors = false;
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
			deadActors.emplace_back(actor);
		}
	}

	//deleting all the dead GameObjetcs
	for (auto actor : deadActors)
	{
		delete actor;
	}
}

void Game::GenOutput()
{
	SDL_SetRenderDrawColor(mRenderer, 220, 220, 220, 255);
	SDL_RenderClear(mRenderer);

	// Draw all sprite components
	for (auto sprite : mSprites)
	{
		sprite->Draw(mRenderer);
	}

	SDL_RenderPresent(mRenderer);
}

void Game::LoadData()
{
	const int numAsteroids = 20;

	for (int i = 0; i < numAsteroids; i++)
	{
		new Asteroid(this);
	}
}

void Game::UnloadData()
{
	// Delete actors
	// Because ~Actor calls RemoveActor, have to use a different style loop
	while (!mActors.empty())
	{
		delete mActors.back();
	}

	// Destroy textures
	for (auto i : mTextures)
	{
		SDL_DestroyTexture(i.second);
	}
	mTextures.clear();
	mTextures.clear();
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

//encapsulating checking, saving, converting and loading texture into a single function
SDL_Texture* Game::GenerateTex(const std::string& fileName)
{
	//initially set as nullptr
	SDL_Texture* tex = nullptr;

	//checking if texture already loaded
	auto iter = mTextures.find(fileName);

	if (iter != mTextures.end())
	{
		tex = iter->second;
	}

	else
	{
		//load from file
		SDL_Surface* surface = IMG_Load(fileName.c_str());
		if (!surface)
		{
			SDL_Log("Couldn't load texture : %s", fileName);
			return nullptr;
		}

		//creating texture from surface
		tex = SDL_CreateTextureFromSurface(mRenderer, surface);
		SDL_FreeSurface(surface);

		if (!tex)
		{
			SDL_Log("Couldnt convert texture from surface : %s", fileName);
			return nullptr;
		}

		mTextures.emplace(fileName.c_str(), tex);
	}

	return tex;
}

void Game::AddAsteroid(Asteroid* ast)
{
	mAsteroids.emplace_back(ast);
}

void Game::RemoveAsteroid(Asteroid* ast)
{
	auto iter = std::find(mAsteroids.begin(),
		mAsteroids.end(), ast);
	if (iter != mAsteroids.end())
	{
		mAsteroids.erase(iter);
	}
}

void Game::AddSprite(SpriteComponent* sprite)
{
	//sprites should be added to the list in order of their drawOrder
	//each time called the sprites draw in the same order

	int currentOrder = sprite->GetDrawOrder();
	auto iter = mSprites.begin();

	//checking if current draw order comes before any of sprites
	for (; iter != mSprites.end(); ++iter)
	{
		if (currentOrder < (*iter)->GetDrawOrder())
		{
			break;
		}
	}

	//inserting at iter position
	mSprites.insert(iter, sprite);

}

void Game::RemoveSprite(SpriteComponent* sprite)
{
	// (We can't swap because it ruins ordering)
	auto iter = std::find(mSprites.begin(), mSprites.end(), sprite);
	mSprites.erase(iter);
}
