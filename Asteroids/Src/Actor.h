#pragma once
#include<vector>
#include"Math.h"
class Actor
{
public:
	
	//To represent and track the state of the game objects
	enum State {
		
		 EActive,
		 Epaused,
		 EDead

	};

	Actor(class Game* game);
	virtual ~Actor();

	//Getters and Setters
	State Getstate() const { return mState; }

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

	State mState;

	std::vector<class component*> mComponents;

	class Game* mGame;

	//Transform properties
	Vector2 mTranslate;

	float mRotation;
	float mScale;

	
};

