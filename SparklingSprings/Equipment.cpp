#include "Equipment.h"

Equipment::Equipment(const ObjectData& _data, const ItemType& _type,
					 const float _damages, const float _protection,
					 const float _durability) : Item(_data, _type)
{
	damages = _damages;
	protection = _protection;
	durability = _durability;
}