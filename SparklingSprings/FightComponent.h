#pragma once
#include "Component.h"
#include "Enemy.h"
#include "Kismet.h"

using namespace std;

class FightComponent : public Component
{
	float range;
	float lightDamages;
	float heavyDamages;
	Vector2f offset;

	//TODO remove
	ShapeObject* hitPoint;

public:
	FightComponent(Actor* _owner);

private:
	Enemy* FindEnemy(HitInfo& _hitInfo);
	void Attack(const float _damages);

public:
	virtual void Update(const float _deltaTime) override;
	void LightAttack();
	void HeavyAttack();
};