#pragma once
#include "IManagable.h"
#include "Item.h"
#include "Button.h"
#include "Label.h"

class ItemData : public IManagable<int>
{
	int count;
	Item* item;
	Label* countText;

public:
	void UpdateCount(const int _factor)
	{
		count += _factor;
		countText->SetString(to_string(count));
	}
	bool IsEmpty() const
	{
		return count == 0;
	}
	int GetCount() const
	{
		return count;
	}
	string GetPath() const
	{
		return item->GetID();
	}
	Label* GetCountText() const
	{
		return countText;
	}

public:
	ItemData(Item* _item, const string& _fontPath);
};

