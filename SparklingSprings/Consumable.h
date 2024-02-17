#pragma once
#include "Item.h"

class Consumable : public Item
{
	float regenValue;

public:
	Consumable(const ObjectData& _data, const ItemType& _type,
			   const float _regenValue);

public:
	//virtual void Consume() override;
};