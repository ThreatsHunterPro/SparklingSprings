#include "ActorManager.h"
#include "TimerManager.h"
#include "InputManager.h"

ActorManager::ActorManager()
{
	interactables = vector<InteractableActor*>();
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

void ActorManager::TryToInteract(const Vector2f& _position, const float _range)
{
	const Vector2f& _mousePosition = InputManager::GetInstance().GetMousePosition();
	if (Distance(_position, _mousePosition) > _range) return;

	for (InteractableActor* _interactable : interactables)
	{
		if (_interactable->GetDrawable()->getGlobalBounds().contains(_mousePosition))
		{
			_interactable->Interact();
		}
	}
}