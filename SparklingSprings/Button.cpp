#include "Button.h"
#include <iostream>

Button::Button(const ObjectData& _data/*, const AllButtonData& _buttonData*/) : Widget(_data)
{
	//allData = _buttonData;
	isSelected = false;
	isHovered = false;
	isHeld = false;
	foreground = nullptr;
}


void Button::OnPressed()
{
	cout << "OnPressed" << endl;
	isSelected = true;
	isHeld = true;
}

void Button::OnHeld()
{
	if (!isHeld) return;

	cout << "OnHeld" << endl;
}

void Button::OnReleased()
{
	if (!isSelected) return;

	cout << "OnReleased" << endl;
	isSelected = false;
	isHeld = false;
}

void Button::OnHovered()
{
	isHovered = true;
}

void Button::OnUnhovered()
{
	isHovered = false;
}


void Button::Execute(const Event& _event)
{

}
