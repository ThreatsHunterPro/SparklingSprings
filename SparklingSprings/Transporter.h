#pragma once
#include "InteractableActor.h"
#include "Player.h"

class Transporter : public InteractableActor
{
	Vector2f destination;

public:
	Transporter(const InteractableData& _data, const Vector2f& _destination);

public:
	void Teleport(Player* _player);
};