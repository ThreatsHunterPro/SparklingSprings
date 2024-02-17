#include "Character.h"

Character::Character(const string& _name, const ObjectData& _data) : Actor(_name, _data)
{
	movement = new MovementComponent(this);
	components.push_back(movement);
	//animation = new AnimationComponent();
}

Character::~Character()
{
	delete movement;
	//delete animation;
}