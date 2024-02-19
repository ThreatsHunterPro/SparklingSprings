#pragma once
#include "Action.h"
#include "MovementComponent.h"

class PlayerMovementComponent : public Component
{
	bool canMove;
	float speed;
	float dashSpeed;
	Vector2f direction;

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

	#pragma region Overworld

	void Sprint();

	#pragma endregion

	#pragma region Overworld

	void Jump();
	void Dash();

	#pragma endregion
};