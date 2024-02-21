#pragma once
#include "ShapeWidget.h"
#include "Item.h"
#include "ProgressBar.h"
#include "Button.h"

struct CraftData
{
	int count;
	ItemInfo info;

	CraftData(const int _count, const ItemInfo& _info)
	{
		count = _count;
		info = _info;
	}
};

struct CraftInfo
{
	vector<CraftData> requiredItems;
	ItemInfo building;

	CraftInfo() = default;

	CraftInfo(const vector<CraftData>& _requiredItems, const ItemInfo& _building)
	{
		requiredItems = _requiredItems;
		building = _building;
	}
};

class Craft
{
	Canvas* canvas;
	CraftInfo info;

public: 
	Canvas* GetCanvasCraft()
	{
		return canvas;
	}

public:
	Craft(const CraftInfo& _info);

private:
	void Init();

public:
	void Build();
};