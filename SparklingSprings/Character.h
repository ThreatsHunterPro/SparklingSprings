#pragma once
#include "MovementComponent.h"
#include "Actor.h"

class Character : public Actor
{
protected:
	MovementComponent* movement;
	//AnimationComponent* animation;

public:
	Character(const string& _name, const ObjectData& _data);
	~Character();
};