#include "PlayerMovementComponent.h"
#include "Actor.h"
#include "Macro.h"

PlayerMovementComponent::PlayerMovementComponent(Actor* _owner) : Component(_owner)
{
	canMove = true;
	speed = 0.1f;
	dashSpeed = 20.0f;
	direction = Vector2f();
}

void PlayerMovementComponent::Update(const float _deltaTime)
{
	if (!canMove) return;

	const Vector2f& _offset = direction * speed * _deltaTime;
	owner->GetDrawable()->move(_offset);
}

void PlayerMovementComponent::Sprint()
{
	cout << "Sprint" << endl;
}

void PlayerMovementComponent::Jump()
{
	cout << "Jump" << endl;
}

void PlayerMovementComponent::Dash()
{
	owner->GetDrawable()->move(direction * dashSpeed);
}