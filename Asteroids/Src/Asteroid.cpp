#include "Asteroid.h"
#include "Game.h"
#include "Random.h"
#include "SpriteComponent.h"
#include "MoveComponent.h"

Asteroid::Asteroid(Game* game) : Actor(game)
{
	//Random position and Random Orientation at time of initialisation

	Vector2 randPos = Random::GetRandomRangeVector(Vector2::zero, Vector2(1024.0f, 768.0f));
	SetPosition(randPos);

	SetRoation(Random::GetRandomRangeFloat(0.0f, (Math::pi * 2)));

	//Create SpriteComponent and add texture
	SpriteComponent* sc = new SpriteComponent(this);
	sc->SetTexture(game->GenerateTex("Assets/Asteroid.png"));

	//Create MovementComponent and set forward speed
	MoveComponent* mc = new MoveComponent(this);
	mc->SetForwardSpeed(150.0f);
}
