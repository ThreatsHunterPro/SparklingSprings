#include "IDamagable.h"
#include "ActorManager.h"

IDamagable::IDamagable(Shape* _shape)
{
	health = nullptr;
	shape = _shape;

	Register();
}


void IDamagable::Register()
{
	ActorManager::GetInstance().AddDamagable(this);
}