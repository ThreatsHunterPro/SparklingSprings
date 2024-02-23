#pragma once
#include "Actor.h"
#include "Timer.h"

class Flame : public Actor
{
	bool canGrow;
	float growSpeed;
	float duration;
	float cooldown;
	float damages;

public:
	void SetCanGrow(const bool _status)
	{
		canGrow = _status;
		shape->setScale(0.0f, shape->getScale().y);
		shape->setFillColor(_status ? Color::White : Color::Transparent);

		if (!canGrow)
		{
			new Timer([&]() { SetCanGrow(true); }, seconds(cooldown));
		}
	}

public:
	Flame(const ShapeData& _data);

public:
	virtual void Update(const float _deltaTime) override;
	void Grow(const float _deltaTime);
	void CheckCollision(const float _deltaTime);
};