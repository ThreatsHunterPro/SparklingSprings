#pragma once
#include "Actor.h"

class ArrowTrap : public Actor
{
	float spawnRate;
	Vector2f offset;
	Vector2f direction;
	ShapeData arrowData;

public:
	ArrowTrap(const ShapeData& _data, const Vector2f& _direction);

private:
	void Init();
	void SpawnArrow();
};