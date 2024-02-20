#include "FightComponent.h"
#include <iostream>

FightComponent::FightComponent(Actor* _owner) : Component(_owner)
{
	range = 50.0f;
	lightDamages = 10.0f;
	heavyDamages = 30.0f;
}


Enemy* FightComponent::FindEnemy()
{
	return nullptr;
}

void FightComponent::Attack(const float _damages)
{
	Enemy* _enemy = FindEnemy();
	_enemy->SetDamages(_damages);
}


void FightComponent::LightAttack()
{
	cout << "LightAttack" << endl;
	Attack(lightDamages);
}

void FightComponent::HeavyAttack()
{
	cout << "HeavyAttack" << endl;
	Attack(heavyDamages);
}