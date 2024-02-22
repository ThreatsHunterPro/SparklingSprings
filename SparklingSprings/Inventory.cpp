#include "Inventory.h"
#include "Button.h"
#include <iostream>

#define FONT "Font.ttf"
#define PATH_CELL ".png"

Inventory::Inventory()
{
	cellSize = Vector2f(50.0f, 50.0f);
	stackSize = 5;

	Init();
}


Button* Inventory::GetFirstAvailableButton() const
{
	for (Button* _button : buttons)
	{
		if (!_button->GetForeground())
		{
			return _button;
		}
	}

	return nullptr;
}

ItemData* Inventory::FindItemData(const string& _path)
{
	for (ItemData* _data : GetAllValues())
	{
		if (_data->GetPath() == _path && _data->GetCount() < stackSize)
		{
			return _data;
		}
	}

	return nullptr;
}


void Inventory::Init()
{
	canvas = new Canvas("PlayerInventory", FloatRect(0, 0, 1, 1));
	canvas->SetVisibilityStatus(false);

	const Vector2f& _gridPos = Vector2f(300.0f, 150.0f);
	const Vector2i& _gridSize = Vector2i(5, 8);

	for (int _rowIndex = 0; _rowIndex < _gridSize.y; _rowIndex++)
	{
		for (int _columnIndex = 0; _columnIndex < _gridSize.x; _columnIndex++)
		{
			const float _posX = _gridPos.x + _columnIndex * cellSize.x;
			const float _posY = _gridPos.y + _rowIndex * cellSize.y;

			Button* _button = new Button(ShapeData(Vector2f(_posX, _posY), cellSize, ""));
			_button->GetDrawable()->setOutlineThickness(3.0f);
			_button->GetDrawable()->setOutlineColor(Color::Blue);

			buttons.push_back(_button);
			canvas->AddWidget(_button);
		}
	}
}

void Inventory::AddItem(const int _count, const string _path, const ItemType& _type, const RarityType& _rarity)
{
	if (_count <= 0) return;

	if (ItemData* _data = FindItemData(_path))
	{
		_data->UpdateCount(1);
		AddItem(_count - 1, _path, _type, _rarity);
		return;
	}
	
	CreateItemData(_path, _type, _rarity);
	AddItem(_count - 1, _path, _type, _rarity);
}

void Inventory::CreateItemData(const std::string& _path, const ItemType& _type, const RarityType& _rarity)
{
	Button* _button = GetFirstAvailableButton();
	if (!_button) return;

	const ShapeData& _objectData = ShapeData(_button->GetObject()->GetShapePosition(),
											 _button->GetObject()->GetShapeSize(), _path);
	Item* _item = new Item(_objectData, _type, _rarity);
	ItemData* _data = new ItemData(_item, FONT);
	Add(_data->GetID(), _data);

	canvas->AddWidget(_item);
	canvas->AddWidget(_data->GetCountText());
	_button->SetForeground(_item);
}