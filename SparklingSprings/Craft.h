#pragma once
#include "ShapeWidget.h"
#include "Item.h"
#include "ProgressBar.h"

struct CraftData
{
	int count;
	Item* item;
};

class Craft : public ShapeWidget
{
	vector<CraftData> requiredItems;
	Object* building;

public:
	Craft(const ShapeData& _data, const vector<CraftData>& _requiredItems,
		  Object* _building);

private:
	void Init();

public:
	void Build();
};