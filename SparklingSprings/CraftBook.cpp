#include "CraftBook.h"
#include "Macro.h"
CraftBook::CraftBook()
{
	cellSize = Vector2f(50.0f, 50.0f);

	// remplacer avec une methode qui lis un fichier TXT
	craftInfos = {
		CraftInfo({
			CraftData(1, ItemInfo(
				"Craft.png",
				ItemType::ITEM_CONSUMABLE,
				RarityType::RARITY_COMMON
			)),
			CraftData(2, ItemInfo(
				"Craft.png",
				ItemType::ITEM_CONSUMABLE,
				RarityType::RARITY_COMMON
			)),
			CraftData(3, ItemInfo(
				"Craft.png",
				ItemType::ITEM_CONSUMABLE,
				RarityType::RARITY_COMMON
			)), 
		},
		ItemInfo(
			"Craft.png",
			ItemType::ITEM_CONSUMABLE,
			RarityType::RARITY_COMMON
		)),
		CraftInfo({
			CraftData(1, ItemInfo(
				"Craft.png",
				ItemType::ITEM_CONSUMABLE,
				RarityType::RARITY_COMMON
			)),
			CraftData(2, ItemInfo(
				"Craft.png",
				ItemType::ITEM_CONSUMABLE,
				RarityType::RARITY_COMMON
			)),
			CraftData(3, ItemInfo(
				"Craft.png",
				ItemType::ITEM_CONSUMABLE,
				RarityType::RARITY_COMMON
			)),
		},
		ItemInfo(
			"Craft.png",
			ItemType::ITEM_CONSUMABLE,
			RarityType::RARITY_COMMON
		)),
	};

	Init();

}

void CraftBook::Init()
{

	canvas = new Canvas("CraftBook", FloatRect(0, 0, 1, 1));

	const Vector2f& _gridPos = Vector2f(100.0f, 100.0f);
	const Vector2i& _gridSize = Vector2i(1, 9);

	//crée des boutons en ligne
	for (int _row = 0, _index = 0; _row < _gridSize.y; _row++)
	{
		for (int _column = 0; _column < _gridSize.x; _column++, _index++)
		{
			const float _posX = _gridPos.x + _column * cellSize.x;
			const float _posY = _gridPos.y + _row * cellSize.y;
			
			static Craft* _craft = new Craft(craftInfos[_index % 2]);

			Button* _button = new Button(ShapeData(Vector2f(_posX, _posY), Vector2f(cellSize.x + 100.0f, cellSize.y), ""), 
				ButtonData({}, {}, [&]() { _craft->GetCanvasCraft()->SetVisibilityStatus(!_craft->GetCanvasCraft()->IsVisible()); }, {}, {}));
			canvas->AddWidget(_button);
		}
	}
}