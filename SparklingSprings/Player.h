#pragma once
#include <string>
#include "Actor.h"
#include "PlayerStats.h"
#include "Inventory.h"
#include "CraftBook.h"
#include "SkillTree.h"
#include "PlayerMovementComponent.h"

using namespace std;

class Player : public Actor
{
	PlayerStats* stats;
	Inventory* inventory;
	CraftBook* craftBook;
	SkillTree* skillTree;
	PlayerMovementComponent* movement;

public:
	Player(const string& _name, const ObjectData& _data);

private:
	void SetupPlayerInput();
	void InitHUD();
	void InitStats();
	void InitSkillTree();

public:
	void Init();
};