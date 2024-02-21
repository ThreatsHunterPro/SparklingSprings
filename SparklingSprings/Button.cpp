#include "Button.h"
#include <iostream>

Button::Button(const ShapeData& _data, const ButtonData& _buttonData) : ShapeWidget(_data)
{
	isSelected = false;
	isHovered = false;
	isHeld = false;
	foreground = nullptr;
	data = _buttonData;
}

void Button::OnPressed()
{
	isSelected = true;
	isHeld = true;
	if (data.pressedCallback)
	{
		data.pressedCallback();
	}
	GetDrawable()->setOutlineThickness(-1.5f); 
	GetDrawable()->setOutlineColor(Color::Red);
	
}

void Button::OnHeld()
{
	if (!isHeld) return;
	if (data.heldCallback)
	{
		data.heldCallback();
	}
}

void Button::OnReleased()
{
	if (!isSelected) return;
	isSelected = false;
	isHeld = false;
	if (data.releasedCallback)
	{
		data.releasedCallback();
	}
	GetDrawable()->setOutlineThickness(-1.5f); 
	GetDrawable()->setOutlineColor(Color::Red);
}

void Button::OnHovered()
{
	isHovered = true;
	if (data.hoveredCallback)
	{
		data.hoveredCallback();
	}
	GetDrawable()->setOutlineThickness(-1.5f); 
	GetDrawable()->setOutlineColor(Color::Blue);
	
}

void Button::OnUnhovered()
{
	isHovered = false;
	if (data.unHoveredCallback)
	{
		data.unHoveredCallback();
	}
	GetDrawable()->setOutlineThickness(-1.5f);
	GetDrawable()->setOutlineColor(Color::Black);
}


void Button::Execute(const Event& _event)
{

}
