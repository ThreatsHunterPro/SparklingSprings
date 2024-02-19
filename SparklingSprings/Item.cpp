#include "Item.h"
#include "Macro.h"
#include "Inventory.h"

Item::Item(const ShapeData& _data, const ItemType& _type,
		   const RarityType& _rarity)
		 : ShapeWidget(_data), IManagable(_data.path)
{
	type = _type;
	rarity = _rarity;
}


void Item::Consume()
{

}