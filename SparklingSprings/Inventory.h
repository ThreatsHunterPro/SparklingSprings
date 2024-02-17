#pragma once
#include "Singleton.h"
#include "IManager.h"
#include "Item.h"
#include "Button.h"

class Inventory : public IManager<int, Item>
{
	Canvas* canvas;
	Vector2f cellSize;
	vector<Button*> allButtons;

public:
	Inventory();

private:
	Button* GetFirstAvailableButton() const;

public:
	void Init();
	void Toggle()
	{
		canvas->SetVisibilityStatus(!canvas->IsVisible());
	}
	/*Widget* Select()
	{
		const Vector2f& _mousePosition = InputManager::GetInstance().GetMousePosition();
		for (Widget* _value : GetAllValues())
		{
			if (_value->GetShape()->getGlobalBounds().contains(_mousePosition))
			{
				return _value;
			}
		}
	}*/

	void AddItem(const string& _path, const ItemType& _type,
				 const RarityType& _rarity = RarityType::RARITY_COMMON);
};