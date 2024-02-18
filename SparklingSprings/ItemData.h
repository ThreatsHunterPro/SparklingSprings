#pragma once
#include "IManagable.h"
#include "Item.h"
#include <string>

using namespace std;

class Inventory;

class ItemData : public IManagable<int>
{
	int count;
	Item* item;
	Inventory* inventory;

public:
	void UpdateCount(const int _factor)
	{
		count += _factor;
	}
	bool IsEmpty() const
	{
		return count == 0;
	}

public:
	ItemData(Item* _item, Inventory* _owner);

private:
	virtual void Register() override;
};

