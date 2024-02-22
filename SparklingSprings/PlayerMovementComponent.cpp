#include "PlayerMovementComponent.h"
#include "Actor.h"
#include "Player.h"
#include "Timer.h"
#include "Ladder.h"

#include "Macro.h"

PlayerMovementComponent::PlayerMovementComponent(Actor* _owner) : Component(_owner)
{
	// Movement
	canMove = true;
	speed = 0.1f;
	direction = Vector2f();
	lastDirection = Vector2f();

	// Sprint
	isSprinting = false;
	sprintSpeed = 0.3f;
	sprintConso = 0.3f;

	// Ground
	isOnGround = false;
	checkGroundDistance = 40.0f;

	canJumpAndDash = false;

	// Jump
	isJumping = false;
	jumpForce = 0.1f;
	jumpDuration = 0.5f;
	gravity = 0.15f;

	// Dash
	canDash = true;
	isDashing = false;
	isResetingDash = false;
	dashSpeed = 0.75f;
	dashDuration = 0.2f;
	dashCooldown = 3.0f;
	dashConso = 400.0f;

	mana = dynamic_cast<Player*>(owner)->GetStats()->mana;

	//TODO remove
	hitPoint = new Actor("HitPoint", ShapeData(Vector2f(), Vector2f(10.0f, 10.0f)));
	hitPoint->GetDrawable()->setFillColor(Color::Green);
}


bool PlayerMovementComponent::CheckGround(HitInfo& _hitInfo, const Vector2f& _direction)
{
	return Raycast(owner->GetShapePosition(), _direction, checkGroundDistance, _hitInfo, {
		owner->GetDrawable(),
		hitPoint->GetDrawable(),
	});
}

void PlayerMovementComponent::Update(const float _deltaTime)
{
	if (!canMove) return;

	Vector2f _offset;
		
	// Déplacement par défaut
	const float _sprintConso = sprintConso * _deltaTime;
	if (isSprinting && mana->GetCurrentValue() >= _sprintConso)
	{
		mana->Update(-_sprintConso);
	}

	const float _finalSpeed = isSprinting ? sprintSpeed : speed;
	_offset = direction * _finalSpeed * _deltaTime;

	// Si je suis en donjon
	if (canJumpAndDash)
	{
		// Si je suis en l'air et que je ne saute pas
		HitInfo _hitInfo;
		isOnGround = CheckGround(_hitInfo, Vector2f(0.0f, 1.0f));
		hitPoint->SetShapePosition(_hitInfo.position);
		hitPoint->GetDrawable()->setFillColor(isOnGround ? Color::Blue : Color::Green);

		if (!isOnGround && !isJumping)
		{
			// Application de la gravité
			_offset = direction + Vector2f(0.0f, 1.0f);
			Normalize(_offset);
			_offset *= gravity * _deltaTime;
		}

		// Si je suis au sol
		else
		{
			// Si je suis en train de dash
			if (isDashing)
			{
				// Application de l'esquive
				_offset = dashDirection * dashSpeed * _deltaTime;
			}

			// Si je suis en train de jump et que je ne dash pas
			else if (isJumping)
			{
				// Application du saut
				_offset = direction + Vector2f(0.0f, -1.0f);
				Normalize(_offset);
				_offset *= jumpForce * _deltaTime;
			}

			// S'il faut que je reset mon dash
			if (!canDash && !isResetingDash)
			{
				isResetingDash = true;
				new Timer([this]() {
					canDash = true;
					isResetingDash = false;
				}, seconds(dashCooldown));
			}
		}
	}

	else
	{
		hitPoint->GetDrawable()->setFillColor(Color::White);
	}

	owner->GetDrawable()->move(_offset);
}

void PlayerMovementComponent::Jump()
{
	if (!isOnGround || isJumping) return;

	isJumping = true;
	new Timer([this]() { isJumping = false; }, seconds(jumpDuration));
}

void PlayerMovementComponent::Dash()
{
	if (!isOnGround || !canDash || isDashing || mana->GetCurrentValue() >= dashConso) return;

	cout << mana->GetCurrentValue() << endl;

	canDash = false;
	isDashing = true;
	dashDirection = direction;
	new Timer([this]() { isDashing = false; }, seconds(dashDuration));
	mana->Update(-dashConso);
}

void PlayerMovementComponent::TryClimbLadder(const float _directionY)
{
	cout << _directionY << endl;
	cout << owner->GetShapePosition().x << " " << owner->GetShapePosition().y << endl;

	const vector<HitInfo>& _hitInfos = RaycastAll(owner->GetShapePosition(), Vector2f(0.0f, _directionY), 5.0f, {
		owner->GetDrawable(),
		hitPoint->GetDrawable(),
	});
	//const bool _hasHit = CheckGround(_hitInfo, Vector2f(0.0f, _directionY));

	for (HitInfo _hitInfo : _hitInfos)
	{
		if (dynamic_cast<Ladder*>(_hitInfo.actor))
		{
			cout << _directionY << endl;
			SetDirectionY(_directionY);
		}

		else
		{
			cout << "ca ce n'est pas une echelle !" << endl;
		}
	}

	if (int(_hitInfos.size()) <= 0)
	{
		SetDirectionY(0.0f);
	}
}