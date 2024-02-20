#pragma once
#include "Component.h"
#include "Enemy.h"

using namespace std;

class FightComponent : public Component
{
	float range;
	float lightDamages;
	float heavyDamages;

public:
	FightComponent(Actor* _owner);

private:
	Enemy* FindEnemy();
	void Attack(const float _damages);

public:
	void LightAttack();
	void HeavyAttack();
};