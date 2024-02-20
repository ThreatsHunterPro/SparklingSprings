#include "PlayerMovementComponent.h"
#include "Actor.h"
#include "Macro.h"
#include "Kismet.h"

PlayerMovementComponent::PlayerMovementComponent(Actor* _owner) : Component(_owner)
{
	canMove = true;
	speed = 0.1f;
	direction = Vector2f();

	isSprinting = false;
	sprintSpeed = 0.3f;

	isOnGround = false;
	checkGroundDistance = 1.7f;

	canJump = false;
	jumpForce = 20.0f;
	gravity = 0.1f;

	dashSpeed = 10.0f;
}


bool PlayerMovementComponent::CheckGround()
{
	HitInfo _hit;
	const bool _hasHit = Raycast(owner->GetShapePosition(), Vector2f(0.0f, 1.0f),
								 checkGroundDistance, _hit, { owner->GetDrawable() });

	return _hasHit;
}

void PlayerMovementComponent::Update(const float _deltaTime)
{
	if (!canMove) return;

	Vector2f _offset;
		
	// OVERWORLD
	// J'avance normalement
	// pas de gravite
	 
	// DONJON
	// J'avance normalement
	// Gravite que si je ne suis pas au sol

	// Jump c'est un Update avec direction UP
	// La gravite ne se reactive que après un temps après avoir sauté

	const float _finalSpeed = isSprinting ? sprintSpeed : speed;
	_offset = direction * _finalSpeed * _deltaTime;

	if (canJump && !(isOnGround = CheckGround()))
	{
		_offset = direction + Vector2f(0.0f, 1.0f);
		Normalize(_offset);
		_offset *= gravity * _deltaTime;
	}

	owner->GetDrawable()->move(_offset);
}

void PlayerMovementComponent::Jump()
{
	if (!isOnGround) return;

	cout << "Jump" << endl;
	const Vector2f& _offset = Vector2f(0.0f, -1.0f) * jumpForce;
	owner->GetDrawable()->move(_offset);
}

void PlayerMovementComponent::Dash()
{
	if (!isOnGround) return;

	cout << "Dash" << endl;
	const Vector2f& _offset = direction * dashSpeed;
	owner->GetDrawable()->move(_offset);
}