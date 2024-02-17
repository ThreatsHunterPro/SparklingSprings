#pragma once
#include "Singleton.h"
#include "IManager.h"
#include "Actor.h"

class ActorManager : public Singleton<ActorManager>, public IManager<string, Actor>
{
public:
	void Update();
};