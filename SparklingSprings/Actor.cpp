#include "Actor.h"
#include "ActorManager.h"

Actor::Actor(const string& _name, const ShapeData& _data)
		   : ShapeObject(_data), IManagable(_name)
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