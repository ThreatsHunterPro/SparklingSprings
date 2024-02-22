#include "InteractComponent.h"
#include "InputManager.h"
#include "ActorManager.h"

InteractComponent::InteractComponent(Actor* _owner) : Component(_owner)
{
	interactRange = 50.0f;
}


void InteractComponent::Interact()
{
	const Vector2f& _mousePosition = InputManager::GetInstance().GetMousePosition();
	const float _distance = Distance(owner->GetShapePosition(), _mousePosition);
	if (_distance > interactRange) return;

	for (IInteractable* _interactable : ActorManager::GetInstance().GetInteractables())
	{
		if (_interactable->GetShape()->getGlobalBounds().contains(_mousePosition))
		{
			_interactable->Interact();
		}
	}
}