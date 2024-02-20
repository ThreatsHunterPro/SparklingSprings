#pragma once
#include "ShapeWidget.h"
#include "IManagable.h"

enum ItemType
{
	ITEM_NONE,
	ITEM_RESOURCE,
	ITEM_CONSUMABLE,
	ITEM_EQUIPMENT
};

enum RarityType
{
	RARITY_COMMON,
	RARITY_RARE,
	RARITY_EPIC,
	RARITY_LEGENDARY
};

class Item : public ShapeWidget, public IManagable<string>
{
	ItemType type;
	RarityType rarity;

public:
	Item(const ShapeData& _data, const ItemType& _type,
		 const RarityType& _rarity = RARITY_COMMON);

public:
	virtual void Consume();
};