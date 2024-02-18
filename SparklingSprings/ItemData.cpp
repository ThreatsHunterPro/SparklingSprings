#include "ItemData.h"
#include "Inventory.h"

ItemData::ItemData(Item* _item, Inventory* _owner) : IManagable(_item->GetID())
{
	count = 0;
	item = _item;
	inventory = _owner;

	Register();
}

void ItemData::Register()
{
	inventory->Add(id, this);
}