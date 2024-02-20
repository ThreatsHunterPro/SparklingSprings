#include "InteractableActor.h"
#include "ActorManager.h"

InteractableActor::InteractableActor(const InteractableData& _data) : Actor(_data.name, _data.data)
{
	Register();

	callback = _data.callback;
}

void InteractableActor::Register()
{
	ActorManager::GetInstance().AddInteractable(this);
}


void InteractableActor::Interact()
{
	if (callback)
	{
		callback();
	}
}