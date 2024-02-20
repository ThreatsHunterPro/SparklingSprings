#pragma once
#include "Actor.h"
#include "Stat.h"

class Enemy : public Actor
{
	Stat* health;

public:
	Enemy(const string& _name, const ShapeData& _data);

private:
	void InitHUD();

public:
	void SetDamages(const float _damages);
};