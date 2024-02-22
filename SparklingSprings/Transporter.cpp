#include "Transporter.h"
#include "Player.h"
#include "Macro.h"

Transporter::Transporter(const ShapeData& _data, const function<void()>& _callback,
						 const Vector2f& _destination)
						: Actor(STRING_ID("Transporter"), _data), IInteractable(GetDrawable(), _callback)
{
	destination = _destination;
}

void Transporter::Teleport(Player* _player)
{
	_player->SetShapePosition(destination);
}