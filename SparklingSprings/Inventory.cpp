#include "Inventory.h"
#include "Button.h"

#define PATH_CELL "Wood.png"

Inventory::Inventory()
{
	cellSize = Vector2f(50.0f, 50.0f);
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

void Inventory::Init()
{
	canvas = new Canvas("PlayerInventory", FloatRect(0, 0, 1, 1));

	const Vector2f& _gridPos = Vector2f(300.0f, 150.0f);
	const Vector2i& _gridSize = Vector2i(4, 5);

	for (int _rowIndex = 0; _rowIndex < _gridSize.y; _rowIndex++)
	{
		for (int _columnIndex = 0; _columnIndex < _gridSize.x; _columnIndex++)
		{
			const float _posX = _gridPos.x + _columnIndex * cellSize.x;
			const float _posY = _gridPos.y + _rowIndex * cellSize.y;

			Button* _button = new Button(ObjectData(Vector2f(_posX, _posY), cellSize, ""));
			_button->GetShape()->setOutlineThickness(3.0f);
			_button->GetShape()->setOutlineColor(Color::Blue);

			buttons.push_back(_button);
			canvas->AddWidget(_button);
		}
	}
}

void Inventory::AddItem(const string& _path, const ItemType& _type, const RarityType& _rarity)
{
	// Je créer des buttons*

	// Je get le buttondata
	// s'il existe j'updatecount
	// sinon j'en créer un 

	/*ButtonData* _data = Get(_path);
	Button* _button = _data ? _data->GetButton() : GetFirstAvailableButton();

	if (!_button) return;
	if (!_data)
	{
		_data = new ButtonData(_button, this);
	}
	
	Item* _item = new Item(ObjectData(_button->GetShapePosition(), cellSize, _path), _type, _rarity);
	_button->SetForeground(_item);
	canvas->AddWidget(_item);*/

	/*Button* _button = GetFirstAvailableButton();
	if (!_button) return;

	Item* _item = new Item(ObjectData(_button->GetShapePosition(), cellSize, _path), _type, _rarity);
	Add(_item->GetID(), _item);
	_button->SetForeground(_item);
	canvas->AddWidget(_item);*/
}