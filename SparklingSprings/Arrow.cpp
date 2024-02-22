#include "Arrow.h"
#include "Macro.h"
#include "Kismet.h"
#include "Player.h"
#include "ActorManager.h"

Arrow::Arrow(const ShapeData& _data, const Vector2f& _direction)
			: Actor(STRING_ID("Arrow"), _data)
{
	moveSpeed = 0.3f;
	direction = _direction;
	damages = 200.0f;
	lifeSpan = 1.0f;

	shape->setScale(_direction.x, 1.0f);
	Init();
}


void Arrow::Init()
{
	Destroy(lifeSpan);
}

void Arrow::Update(const float _deltaTime)
{
	Actor::Update(_deltaTime);

	Move(_deltaTime);
	CheckCollision();
}

void Arrow::Move(const float _deltaTime)
{
	const Vector2f& _offset = direction * moveSpeed * _deltaTime;
	const Vector2f& _destination = GetShapePosition() + _offset;
	SetShapePosition(_destination);
}

void Arrow::CheckCollision()
{
	const vector<Actor*>& _actors = Boxcast(GetDrawable(), ActorManager::GetInstance().GetAllValues());

	for (Actor* _actor : _actors)
	{
		if (IDamagable* _damagable = dynamic_cast<IDamagable*>(_actor))
		{
			_damagable->TakeDamages(damages);
			Destroy();
			return;
		}
	}

	if (_actors.size() > 0)
	{
		Destroy();
	}
}