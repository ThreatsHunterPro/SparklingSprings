#pragma once
#include "Item.h"

class Equipment : public Item
{
	float damages;
	float protection;
	float durability;

public:
	Equipment(const ObjectData& _data, const ItemType& _type,
		const float _damages, const float _protection,
		const float _durability);
};