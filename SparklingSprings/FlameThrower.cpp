#include "FlameThrower.h"
#include "Macro.h"
#include "Kismet.h"
#include "ActorManager.h"

#define PATH_FLAME "GPEs/Flame.png"

FlameThrower::FlameThrower(const ShapeData& _data, const Vector2f& _direction)
						 : Actor(STRING_ID("FlameThrower"), _data)
{
	range = 300.0f;
	direction = _direction;
	const float _finalRange = direction.x > 0.0f ? range : -range;
	flame = new ShapeObject(ShapeData(Vector2f(_data.position.x + _finalRange / 2.0f, _data.position.y), Vector2f(range, 50.0f), PATH_FLAME));
	
	SetCanGrow(true);
	canGrow = true;
	growSpeed = 0.1f;
	duration = 2.0f;
	damages = 0.2f;
	cooldown = 3.0f;
}


void FlameThrower::Update(const float _deltaTime)
{
	Actor::Update(_deltaTime);

	Grow(_deltaTime);
	CheckCollision(_deltaTime);
}

void FlameThrower::Grow(const float _deltaTime)
{
	if (!canGrow) return;

	if (!willStop && flame->GetDrawable()->getScale().x >= 1.0f)
	{
		new Timer([&]() { SetCanGrow(false); }, seconds(duration));
		willStop = true;
		return;
	}

	const float _newScaleX = flame->GetDrawable()->getScale().x + growSpeed * _deltaTime * 0.001f;
	//flame->GetDrawable()->setScale(_newScaleX, flame->GetDrawable()->getScale().y);
	cout << _newScaleX << " " << flame->GetDrawable()->getScale().y << endl;
	//SetShapePosition(GetShapePosition() + Vector2f(, 0.0f))
}

void FlameThrower::CheckCollision(const float _deltaTime)
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