#pragma once
#include "Singleton.h"
#include "IManager.h"
#include "Actor.h"
#include "IInteractable.h"
#include "IDamagable.h"

class ActorManager : public Singleton<ActorManager>, public IManager<string, Actor>
{
	vector<IInteractable*> interactables;
	vector<IDamagable*> damagables;

public:
	void AddInteractable(IInteractable* _interactable)
	{
		interactables.push_back(_interactable);
	}
	void AddDamagable(IDamagable* _damagable)
	{
		damagables.push_back(_damagable);
	}
	vector<IInteractable*> GetInteractables() const
	{
		return interactables;
	}
	vector<IDamagable*> GetDamagables() const
	{
		return damagables;
	}

public:
	ActorManager();

public:
	void Update();
};