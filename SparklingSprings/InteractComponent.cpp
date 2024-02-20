#include "InteractComponent.h"
#include "ActorManager.h"

InteractComponent::InteractComponent(Actor* _owner) : Component(_owner)
{
	interactRange = 50.0f;
}


void InteractComponent::Interact()
{
	ActorManager::GetInstance().TryToInteract(owner->GetShapePosition(), interactRange);
}