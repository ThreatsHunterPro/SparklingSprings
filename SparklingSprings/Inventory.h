#pragma once
#include "IManager.h"
#include "ItemData.h"
#include "Canvas.h"
#include "Button.h"

class Inventory : public IManager<int, ItemData>
{
	Canvas* canvas;
	Vector2f cellSize;
	vector<Button*> buttons;
	int stackSize;
 
public:
	Inventory();

private:
	Button* GetFirstAvailableButton() const;
	ItemData* FindItemData(const string& _path);

public:
	void Init();
	void Toggle()
	{
		canvas->SetVisibilityStatus(!canvas->IsVisible());
	}
	void AddItem(const int _count, const string _path, const ItemType& _type, const RarityType& _rarity = RARITY_COMMON);
	void CreateItemData(const std::string& _path, const ItemType& _type, const RarityType& _rarity);
};