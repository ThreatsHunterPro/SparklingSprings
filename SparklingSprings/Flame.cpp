#include "Flame.h"
#include "Macro.h"
#include "Kismet.h"
#include "ActorManager.h"

Flame::Flame(const ShapeData& _data) : Actor(STRING_ID("Flame"), _data)
{
	canGrow = true;
	growSpeed = 0.1f;
	duration = 2.0f;
	damages = 0.2f;
	cooldown = 3.0f;
}

void Flame::Update(const float _deltaTime)
{
	Actor::Update(_deltaTime);

	Grow(_deltaTime);
	CheckCollision(_deltaTime);
}

void Flame::Grow(const float _deltaTime)
{
	if (!canGrow) return;

	if (shape->getScale().x >= 1.0f)
	{
		new Timer([&]() { SetCanGrow(false); }, seconds(duration));
		return;
	}

	const float _newScaleX = shape->getScale().x + growSpeed * _deltaTime * 0.001f;
	shape->setScale(_newScaleX, shape->getScale().y);
	//SetShapePosition(GetShapePosition() + Vector2f(, 0.0f))
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