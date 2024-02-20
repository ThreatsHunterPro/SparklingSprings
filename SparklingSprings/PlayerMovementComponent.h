#pragma once
#include "Action.h"
#include "MovementComponent.h"

class PlayerMovementComponent : public Component
{
	bool canMove;
	float speed;
	Vector2f direction;

	bool isSprinting;
	float sprintSpeed;

	bool isOnGround;
	float checkGroundDistance;

	bool canJump;
	float jumpForce;
	float gravity;

	float dashSpeed;

public:
	void SetDirectionX(const float _directionX)
	{
		direction.x = _directionX;
	}
	void SetDirectionY(const float _directionY)
	{
		direction.y = _directionY;
	}
	void SetSprint(const bool _status)
	{
		isSprinting = _status;
	}
	void SetCanJump(const bool _status)
	{
		canJump = _status;
	}

public:
	PlayerMovementComponent(Actor* _owner);

private:
	bool CheckGround();

public:
	virtual void Update(const float _deltaTime) override;
	void Jump();
	void Dash();
};