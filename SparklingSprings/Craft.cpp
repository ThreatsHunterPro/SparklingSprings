#include "Craft.h"
#include "Macro.h"

Craft::Craft(const CraftInfo& _info)
{
	info = _info;
	Init();
}

void Craft::Init()
{
	canvas = new Canvas(STRING_ID("Craft"), FloatRect(0, 0, 1, 1));

	Button* _button = new Button(ShapeData(Vector2f(500.0f, 200.0f), Vector2f(100.0f, 100.0f), "Craft.png"));

	canvas->AddWidget(_button);

	//const Vector2f _cellSizeBuild = cellSize * 2.0f;
	//const Vector2f _positionBuild = Vector2f(700.0f, 200.0f);

	//Button* _buildButton = new Button(ShapeData(_positionBuild, _cellSizeBuild, pathsBuild[0]));
	//_buildButton->GetDrawable()->setOrigin(_buildButton->GetDrawable()->getLocalBounds().width / 2.0f, _buildButton->GetDrawable()->getLocalBounds().height / 2.0f);
	//canvas->AddWidget(_buildButton);

	//const Vector2f _cellSizeRequiered = cellSize * 1.5f;

	//for (int _index = 0; _index < pathsItems.size(); _index++)
	//{

	//	float _posX = 300.0f + _index * 50;
	//	float _posY = 150.0f;
	//	//creation requieredItems
	//	Button* _itemRequiered = new Button(ShapeData(Vector2f(_posX, _posY) * 2.0f, _cellSizeRequiered, pathsItems[_index]));
	//	_itemRequiered->GetDrawable()->setOrigin(_itemRequiered->GetDrawable()->getLocalBounds().width / 2.0f, _itemRequiered->GetDrawable()->getLocalBounds().height / 2.0f);
	//	canvas->AddWidget(_itemRequiered);
	//}
	////crée un craft avec des requiteredItems donc un nombre d'item
	////building est l'item qui va etre crafter

}

void Craft::Build()
{
	

	//TODO remove items from player's inventory
	//for (Item* _item : requiredItems)
	//{
	//	_item->SetToRemove(true);
	//}

}