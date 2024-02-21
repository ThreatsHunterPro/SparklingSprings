#include "Transporter.h"

Transporter::Transporter(const InteractableData& _data, const Vector2f& _destination)
						: InteractableActor(_data)
{
	destination = _destination;
}


void Transporter::Teleport(Player* _player)
{
	_player->SetShapePosition(destination);
}