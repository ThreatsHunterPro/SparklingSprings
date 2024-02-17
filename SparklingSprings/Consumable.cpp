#include "Consumable.h"

Consumable::Consumable(const ObjectData& _data, const ItemType& _type,
					   const float _regenValue)
					 : Item(_data, _type, RarityType::RARITY_COMMON)
{
	regenValue = _regenValue;
}