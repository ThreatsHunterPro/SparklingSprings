#include "Actor.h"
#include "Macro.h"
#include "ActorManager.h"

Actor::Actor(const string& _name, const ObjectData& _data) : Object(_data),
															IManagable(to_string(GetUniqueID()) + _name)
{
	Register();
}


void Actor::Register()
{
	ActorManager::GetInstance().Add(id, this);
}


void Actor::Update(const float _deltaTime)
{
	for (Component* _component : components)
	{
		_component->Update(_deltaTime);
	}
}