#include "FightComponent.h"
#include "Player.h"
#include "PlayerMovementComponent.h"

FightComponent::FightComponent(Actor* _owner) : Component(_owner)
{
	range = 100.0f;
	offset = Vector2f(20.0f, 50.0f);

	lightDamages = 10.0f;
	lightConso = 100.0f;

	heavyDamages = 30.0f;
	heavyConso = 300.0f;

	//TODO remove
	hitPoint = new Actor("HitPoint", ShapeData(Vector2f(), Vector2f(10.0f, 10.0f)));
	hitPoint->GetDrawable()->setFillColor(Color::Red);

	mana = dynamic_cast<Player*>(owner)->GetStats()->mana;
}


Enemy* FightComponent::FindEnemy(HitInfo& _hitInfo)
{
	PlayerMovementComponent* _movement = owner->GetComponent<PlayerMovementComponent>();
	const bool _hasHit = Raycast(owner->GetShapePosition() + offset, _movement->GetLastDirection(), range,
								 _hitInfo, {
									 owner->GetDrawable(),
									 hitPoint->GetDrawable(),
								});

	return _hasHit ? dynamic_cast<Enemy*>(_hitInfo.actor) : nullptr;
}

void FightComponent::Attack(const float _damages)
{
	HitInfo _hitInfo;
	Enemy* _enemy = FindEnemy(_hitInfo);
	if (!_enemy) return;
	_enemy->SetDamages(_damages);
}



void FightComponent::Update(const float _deltaTime)
{
	HitInfo _hitInfo;
	const bool _enemyFound = FindEnemy(_hitInfo);
	hitPoint->SetShapePosition(_hitInfo.position);
}

void FightComponent::LightAttack()
{
	Attack(lightDamages);
	mana->Update(-lightConso);
}

void FightComponent::HeavyAttack()
{
	Attack(heavyDamages);
	mana->Update(-heavyConso);
}