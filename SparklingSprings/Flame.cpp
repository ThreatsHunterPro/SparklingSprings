#include "Flame.h"
#include "Macro.h"
#include "Kismet.h"
#include "ActorManager.h"

Flame::Flame(const ShapeData& _data) : Actor(STRING_ID("Flame"), _data)
{
	isActive = false;
	duration = 2.0f;
	damages = 0.2f;
}

void Flame::Update(const float _deltaTime)
{
	Actor::Update(_deltaTime);
	CheckCollision(_deltaTime);
}

void Flame::CheckCollision(const float _deltaTime)
{
	const vector<Actor*>& _actors = Boxcast(GetDrawable(), ActorManager::GetInstance().GetAllValues());

	for (Actor* _actor : _actors)
	{
		if (IDamagable* _damagable = dynamic_cast<IDamagable*>(_actor))
		{
			_damagable->TakeDamages(damages * _deltaTime);
			return;
		}
	}
}