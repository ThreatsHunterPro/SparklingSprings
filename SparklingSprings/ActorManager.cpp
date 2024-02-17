#include "ActorManager.h"
#include "TimerManager.h"

void ActorManager::Update()
{
	const float _deltaTime = TimerManager::GetInstance().GetDeltaTime();

	for (Actor* _actor : GetAllValues())
	{
		_actor->Update(_deltaTime);
	}

	GarbageValues();
}