#pragma once
#include "Actor.h"
#include "IInteractable.h"

class Player;

class Transporter : public Actor, public IInteractable
{
	Vector2f destination;

public:
	Transporter(const ShapeData& _data, const function<void()>& _callback, const Vector2f& _destination);

public:
	void Teleport(Player* _player);
};