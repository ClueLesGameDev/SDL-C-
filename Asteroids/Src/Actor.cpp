#include "Actor.h"
#include "Game.h"
#include "Component.h"
#include <algorithm>

Actor::Actor(Game* game) 
	: mState(EActive), mPosition(Vector2::zero),
	  mRotation(0.0f), mScale(1.0f),
	  mGame(game)
{
	game->AddActor(this);
}

Actor::~Actor()
{
	mGame->RemoveActor(this);

	//delete all components
	while (!mComponents.empty())
	{
		delete mComponents.back();
	}
}

void Actor::Update(float dt)
{
	if (mState == EActive)
	{
		UpdateComponents(dt);
		UpdateActor(dt);
	}
}

void Actor::UpdateComponents(float dt)
{
	for (auto comp : mComponents)
	{
		comp->Update(dt);
	}
}

void Actor::UpdateActor(float dt)
{
}

void Actor::AddComponent(Component* component)
{
}

void Actor::RemoveComponent(Component* component)
{
}
