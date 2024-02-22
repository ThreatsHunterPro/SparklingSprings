#pragma once
#include "Actor.h"
#include "Flame.h"

class FlameThrower : public Actor
{
	float cooldown;
	float range;
	Vector2f direction;
	Flame* flame;

public:
	FlameThrower(const ShapeData& _data, const Vector2f& _direction);

private:
	void Init();
	void ToogleFlame();
};