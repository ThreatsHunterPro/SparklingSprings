#pragma once
#include "Actor.h"

class Flame : public Actor
{
	bool isActive;
	float duration;
	float damages;

public:
	void ToggleStatus()
	{
		isActive = !isActive;
		const float _scale = isActive ? 1.0f : 0.0f;
		shape->setScale(_scale, _scale);
	}

public:
	Flame(const ShapeData& _data);

public:
	virtual void Update(const float _deltaTime) override;
	void CheckCollision(const float _deltaTime);
};