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

			static Button* _button = new Button(ShapeData(Vector2f(_posX, _posY), cellSize, ""), ButtonData(
				[&]() {_button->GetDrawable()->setOutlineThickness(-1.5f); _button->GetDrawable()->setOutlineColor(Color::Blue); },		//hovered 
				[&]() {_button->GetDrawable()->setOutlineThickness(-1.5f); _button->GetDrawable()->setOutlineColor(Color::Black); },	  	//unhovered 
				[&]() {_button->GetDrawable()->setOutlineThickness(-1.5f); _button->GetDrawable()->setOutlineColor(Color::Red); },		//pressed 
				[&]() {_button->GetDrawable()->setOutlineThickness(-1.5f); _button->GetDrawable()->setOutlineColor(Color::Black); },	  	//released 
				[&]() {_button->GetDrawable()->setOutlineThickness(-1.5f); _button->GetDrawable()->setOutlineColor(Color::Green); }		//held
				));

			buttons.push_back(_button);
			canvas->AddWidget(_button);
		}
	}
}

//void CraftBook::BuildSelected()
//{
//	for (Button* _button : buttons)
//	{
//		if (_button->IsSelected())
//		{
//			//action affectuer
//			_button->GetDrawable()->setOutlineThickness(-3.0f);
//			_button->GetDrawable()->setOutlineColor(Color::Green);
//		}
//		else
//		{
//			_button->GetDrawable()->setOutlineThickness(-1.5f);
//			_button->GetDrawable()->setOutlineColor(Color::Black);
//		}
//	}
//}
