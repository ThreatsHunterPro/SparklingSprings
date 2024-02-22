#include "ActorManager.h"
#include "TimerManager.h"
#include "InputManager.h"

ActorManager::ActorManager()
{
	interactables = vector<IInteractable*>();
	damagables = vector<IDamagable*>();
}


void ActorManager::Update()
{
	const float _deltaTime = TimerManager::GetInstance().GetDeltaTime();

	for (Actor* _actor : GetAllValues())
	{
		_actor->Update(_deltaTime);
	}

	GarbageValues();
}