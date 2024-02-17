#pragma once
#include "Widget.h"
#include "Item.h"

class Craft : public Widget
{
	vector<Item*> requiredItems;
	Object* building;

public:
	Craft(const ObjectData& _data, const vector<Item*>& _requiredItems,
		  Object* _building);

public:
	void Build();
};