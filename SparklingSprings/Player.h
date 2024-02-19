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
	Player(const string& _name, const ShapeData& _data);

private:
	void SetupPlayerInput();
	void InitHUD();
	void InitStats();
	void InitSkillTree();

	//TODO move
	void LightAttack();
	void HeavyAttack();

public:
	void Init();
};