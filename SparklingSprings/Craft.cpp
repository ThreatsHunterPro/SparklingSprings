#include "Craft.h"

Craft::Craft(const ShapeData& _data, const vector<CraftData>& _requiredItems,
	Object* _building) : ShapeWidget(_data)
{
	requiredItems = _requiredItems;
	building = _building;
	Init();
}

void Craft::Init()
{
	//crée un craft avec des requiteredItems donc un nombre d'item
	//building est l'item qui va etre crafter
}

void Craft::Build()
{
	

	//TODO remove items from player's inventory
	//for (Item* _item : requiredItems)
	//{
	//	_item->SetToRemove(true);
	//}

}