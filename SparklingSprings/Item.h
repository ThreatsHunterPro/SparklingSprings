#pragma once
#include "Widget.h"

enum ItemType
{
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

class Item : public Widget, public IManagable<int>
{
	ItemType type;
	RarityType rarity;

public:
	Item(const ObjectData& _data, const ItemType& _type,
		 const RarityType& _rarity = RARITY_COMMON);

private:
	virtual void Register() override;

public:
	virtual void Consume();


};