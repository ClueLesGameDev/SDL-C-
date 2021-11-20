#pragma once
#include <vector>
#include "Math.h"
#include "Game.h"
#include <SDL.h>
class Actor
{
public:
	
	//To represent and track the state of the game objects
	enum State {
		
		 EActive,
		 Epaused,
		 EDead

	};

	Actor(Game* game);
	virtual ~Actor();

	//Getters and Setters
	State		Getstate() const	{ return mState; }

	float		GetScale() const	{ return mScale; }
	void		SetScale(float scale) { mScale = scale; }

	Vector2		GetPosition() const { return mPosition; }
	
	float		GetRoation() const	{ return mRotation; }		//returns angle in radian
	void		SetRoation(float rotVal) { mRotation = rotVal; }

	void		SetPosition(Vector2 position) { mPosition = position; }

	//function to return the rotated value.
	Vector2 GetForward() const
	{
		//SDL graphics use +ve y axis through downward direction use negative axis
		return Vector2{ Math::Cos(mRotation), -Math::Sin(mRotation) };
	}


	//called from the game not overridable
	void Update(float dt);

	//Updates the componenets attached to the gameobject
	void UpdateComponents(float dt);

	//Any actor specific updates(overriden for each actor subclass)
	virtual void UpdateActor(float dt);

	//Functions to add and remove components
	void AddComponent(class Component* component);
	void RemoveComponent(class Component* component);	

private:

	//CUrrent state of the gameobject
	State mState;

	std::vector<class Component*> mComponents;

	Game* mGame;

	//Transform properties
	Vector2 mPosition;
	float mRotation;
	float mScale;

	
};

