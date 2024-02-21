#include "Equipment.h"

Equipment::Equipment(const ShapeData& _data, const ItemType& _type,
	const float _damages, const float _protection,
	const float _durability, const int _layer) : Item(_data, _type,_layer)
{
	damages = _damages;
	protection = _protection;
	durability = _durability;
}