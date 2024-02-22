#include "Actor.h"
#include "ActorManager.h"
#include "Timer.h"

Actor::Actor(const string& _name, const ShapeData& _data)
		   : ShapeObject(_data), IManagable(_name)
{
	Register();
	SetOriginAtMiddle(GetDrawable());
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

void Actor::Destroy(const float _waitingTime)
{
	new Timer([&]() { SetToRemove(true); }, seconds(_waitingTime));
}