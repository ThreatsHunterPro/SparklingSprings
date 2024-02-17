#include "Item.h"
#include "Macro.h"
#include "Inventory.h"

Item::Item(const ObjectData& _data, const ItemType& _type,
		   const RarityType& _rarity)
		 : Widget(_data), IManagable(GetUniqueID())
{
	type = _type;
	rarity = _rarity;
}


void Item::Consume()
{

}