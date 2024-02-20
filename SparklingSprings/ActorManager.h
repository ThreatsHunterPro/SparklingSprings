#pragma once
#include "Singleton.h"
#include "IManager.h"
#include "Actor.h"
#include "InteractableActor.h"

class ActorManager : public Singleton<ActorManager>, public IManager<string, Actor>
{
	vector<InteractableActor*> interactables;

public:
	void AddInteractable(InteractableActor* _interactable)
	{
		interactables.push_back(_interactable);
	}

public:
	ActorManager();

public:
	void Update();
	void TryToInteract();
};