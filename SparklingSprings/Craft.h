#pragma once
#include "ShapeWidget.h"
#include "Item.h"

class Craft : public ShapeWidget
{
	vector<Item*> requiredItems;
	Object* building;

public:
	Craft(const ShapeData& _data, const vector<Item*>& _requiredItems,
		  Object* _building,const int _layer);

public:
	void Build();
};