#include "InteractableActor.h"
#include "ActorManager.h"

InteractableActor::InteractableActor(const string& _name, const ShapeData& _data,
									 const function<void()>& _callback) : Actor(_name, _data)
{
	Register();

	callback = _callback;
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