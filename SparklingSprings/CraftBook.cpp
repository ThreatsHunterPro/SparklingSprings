#include "CraftBook.h"

CraftBook::CraftBook()
{
	cellSize = Vector2f(50.0f, 50.0f);
	Init();
}

void CraftBook::Init()
{
	canvas = new Canvas("CraftBook", FloatRect(0, 0, 1, 1));

	const Vector2f& _gridPos = Vector2f(700.0f, 350.0f);
	const Vector2i& _gridSize = Vector2i(3, 3);


	for (int _i = 0; _i < _gridSize.y; _i++)
	{
		for (int _j = 0; _j < _gridSize.x; _j++)
		{
			const float _posX = _gridPos.x + _j * cellSize.x;
			const float _posY = _gridPos.y + _i * cellSize.y;

			Button* _button = new Button(ShapeData(Vector2f(_posX, _posY), cellSize, ""));
			canvas->AddWidget(_button);

			//bar de chargement qui load vers le haut pour le temps de craft de charque item
			ProgressBar* _craftingBar = new ProgressBar(ShapeData(Vector2f(_posX, _posY), Vector2f(50.0f, 50.0f), "Craft.png"),
				canvas, "", ProgressType::PT_TOP, 1000.0f);
			canvas->AddWidget(_craftingBar);

			//button->progressBarTimer->ChangeValue(craft->GetDuration());
		}
	}
}
