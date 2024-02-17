#include "PlayerMovementComponent.h"
#include "Actor.h"
#include "Macro.h"

PlayerMovementComponent::PlayerMovementComponent(Actor* _owner) : Component(_owner)
{
	canMove = true;
	direction = Vector2f();
	speed = 0.1f;
}

void PlayerMovementComponent::Update(const float _deltaTime)
{
	if (!canMove) return;

	const Vector2f& _offset = direction * speed * _deltaTime;
	owner->GetShape()->move(_offset);
}