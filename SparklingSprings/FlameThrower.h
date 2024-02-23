#pragma once
#include "Actor.h"
#include "Timer.h"

class FlameThrower : public Actor
{
	float range;
	Vector2f direction;
	ShapeObject* flame;

	bool canGrow;
	bool willStop;
	float growSpeed;
	float duration;
	float damages;
	float cooldown;

public:
	void SetCanGrow(const bool _status)
	{
		canGrow = _status;
		willStop = !_status;

		flame->GetDrawable()->setScale(0.0f, flame->GetDrawable()->getScale().y);
		//flame->GetDrawable()->setFillColor(_status ? Color::White : Color::Transparent);

		if (!canGrow)
		{
			new Timer([&]() { SetCanGrow(true); }, seconds(cooldown));
		}
	}

public:
	FlameThrower(const ShapeData& _data, const Vector2f& _direction);

public:
	virtual void Update(const float _deltaTime) override;
	void Grow(const float _deltaTime);
	void CheckCollision(const float _deltaTime);
};