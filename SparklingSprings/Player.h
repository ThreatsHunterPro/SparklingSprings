#pragma once
#include <string>
#include "Actor.h"
#include "PlayerStats.h"
#include "PlayerMovementComponent.h"

using namespace std;

class Player : public Actor
{
	PlayerStats* stats;
	PlayerMovementComponent* movement;

public:
	Player(const string& _name, const ObjectData& _data);

private:
	void SetupPlayerInput();
	void InitHUD();

public:
	void Init();
};