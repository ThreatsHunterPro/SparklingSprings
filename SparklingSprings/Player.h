#pragma once
#include "Actor.h"
#include "PlayerStats.h"
#include "Inventory.h"
#include "CraftBook.h"
#include "SkillTree.h"
#include "PlayerMovementComponent.h"
#include "ActionMap.h"

using namespace std;

class Player : public Actor
{
	PlayerStats* stats;
	Inventory* inventory;
	CraftBook* craftBook;
	SkillTree* skillTree;
	PlayerMovementComponent* movement;
	ActionMap* overworldActionMap;
	ActionMap* donjonActionMap;

public:
	Player(const string& _name, const ShapeData& _data);

private:
	void SetupPlayerInput();
	void InitHUD();
	void InitStats();
	void InitSkillTree();

	//TODO move
	void SwapActionMap();

	//TODO move
	void LightAttack();
	void HeavyAttack();

public:
	void Init();
};