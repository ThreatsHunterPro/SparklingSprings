#include "ItemData.h"
#include "Macro.h"

ItemData::ItemData(Item* _item, const string& _fontPath) : IManagable(GetUniqueID())
{
	count = 1;
	item = _item;
	countText = new Label(TextData(to_string(count), _item->GetObject()->GetShapePosition(), _fontPath, 20, Color::Red));
}