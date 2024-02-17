#pragma once
#include "Character.h"
#include "Unit.h"
#include "Spell.h"

struct PlayerStats
{
	vector<Unit*> units;
	vector<Spell*> spells;

	int loadingBarSize;
	float loadingBarSpeed;
};

class Player : public Character
{
	PlayerStats stats;

public:
	Player(const string& _name, const ObjectData& _data);

private:
	void SetupPlayerInput();
	void InitHUD();
};