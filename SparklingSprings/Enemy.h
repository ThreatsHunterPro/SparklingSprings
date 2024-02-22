#pragma once
#include "Actor.h"
#include "IDamagable.h"
#include "Stat.h"

class Enemy : public Actor, public IDamagable
{
	Vector2f barOffset;
	Stat* health;

public:
	Enemy(const string& _name, const ShapeData& _data);

private:
	void InitHUD();

public:
	virtual void Update(const float _deltaTime) override;
	void SetDamages(const float _damages);
};