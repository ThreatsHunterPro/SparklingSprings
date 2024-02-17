#pragma once
#include <string>
#include "Actor.h"
using namespace std;

class Player : public Actor
{
public:
	Player(const string& _name, const ObjectData& _data);

private:
	void SetupPlayerInput();
	void InitHUD();
};