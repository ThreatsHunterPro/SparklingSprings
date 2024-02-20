#pragma once
#include "Component.h"

class InteractComponent : public Component
{
	float interactRange;

public:
	InteractComponent(Actor* _owner);

public:
	void Interact();
};