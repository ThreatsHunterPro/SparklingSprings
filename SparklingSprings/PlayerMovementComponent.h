#pragma once
#include "Action.h"
#include "MovementComponent.h"

class PlayerMovementComponent : public Component
{
	bool canMove;
	Vector2f direction;
	float speed;

public:
	void SetDirectionX(const float _directionX)
	{
		direction.x = _directionX;
	}
	void SetDirectionY(const float _directionY)
	{
		direction.y = _directionY;
	}

public:
	PlayerMovementComponent(Actor* _owner);

public:
	virtual void Update(const float _deltaTime) override;
};