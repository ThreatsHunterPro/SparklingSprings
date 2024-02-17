#pragma once
#include <string>
#include "Actor.h"
#include "PlayerStats.h"

using namespace std;

class Player : public Actor
{
	PlayerStats stats;

public:
	Player(const string& _name, const ObjectData& _data);

private:
	void SetupPlayerInput();
	void InitHUD();
};