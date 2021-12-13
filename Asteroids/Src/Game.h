#pragma once
#include <SDL.h>
#include <unordered_map>
#include <string>
#include <vector>


class Game
{
public:
	Game();
	~Game();

	bool Initialize();
	void Run();
	void Exit();


	void AddActor(class Actor* actor);
	void RemoveActor(class Actor* actor) {};

	void AddSprite(class SpriteComponent* sprite);
	void RemoveSprite(class SpriteComponent* sprite);

	SDL_Texture* GenerateTex(const std::string& fileName);

	// Game-specific (add/remove asteroid)
	void AddAsteroid(class Asteroid* ast);
	void RemoveAsteroid(class Asteroid* ast);
	std::vector<class Asteroid*>& GetAsteroids() { return mAsteroids; }

private:

	void InputProcess();
	void Update();
	void GenOutput();

	void LoadData();
	void UnloadData();

	bool mIsRunning;
	bool mIsUpdatingActors;			//to see wether the actors are getting updated and is iterating.

	SDL_Window* mWindow;
	SDL_Renderer* mRenderer;

	std::vector<class Actor*> mActors;
	std::vector<class Actor*> mPendingActors;

	std::vector<class SpriteComponent*> mSprites;

	std::vector<class Asteroid*> mAsteroids;

	std::unordered_map<std::string, SDL_Texture*> mTextures;

	Uint32 mTicksCount;
};