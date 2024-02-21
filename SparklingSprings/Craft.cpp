#include "Craft.h"

Craft::Craft(const ShapeData& _data, const vector<Item*>& _requiredItems,
			 Object* _building,const int _layer) : ShapeWidget(_data,_layer)
{
	requiredItems = _requiredItems;
	building = _building;
}

void Craft::Build()
{
	//cout << "Build building !" << endl;
	//TODO remove items from player's inventory
}