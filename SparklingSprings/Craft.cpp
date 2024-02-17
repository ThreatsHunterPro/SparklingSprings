#include "Craft.h"

Craft::Craft(const ObjectData& _data, const vector<Item*>& _requiredItems,
			 Object* _building) : Widget(_data)
{
	requiredItems = _requiredItems;
	building = _building;
}

void Craft::Build()
{
	cout << "Build building !" << endl;
	//TODO remove items from player's inventory
}