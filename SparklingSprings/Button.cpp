#include "Button.h"
#include <iostream>

Button::Button(const ObjectData& _data, const AllButtonData& _buttonData) : Widget(_data)
{
	allData = _buttonData;
	isSelected = false;
	isHeld = false;
}


void Button::OnPressed()
{
	cout << "OnPressed" << endl;
	isSelected = true;
	isHeld = true;
	shape->setOutlineThickness(5.0f);
	shape->setOutlineColor(Color::Red);
}

void Button::OnHeld()
{
	cout << "OnHeld" << endl;
}

void Button::OnReleased()
{
	cout << "OnReleased" << endl;
	isHeld = false;
	shape->setOutlineThickness(0.0f);
}

void Button::OnHovered()
{
	cout << "OnHovered" << endl;
	shape->setOutlineThickness(5.0f);
	shape->setOutlineColor(Color::Yellow);
}

void Button::OnUnhovered()
{
	cout << "OnUnhovered" << endl;
	shape->setOutlineThickness(0.0f);
}