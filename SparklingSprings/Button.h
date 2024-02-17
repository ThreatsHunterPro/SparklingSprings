#pragma once
#include "Widget.h"
#include <functional>

using namespace std;

struct ButtonData
{
	Color color;
	float outlineThickness;
	Color outlineColor;

	ButtonData() = default;
	ButtonData(const Color& _color,
		const float _outlineThickness, const Color& _outlineColor)
	{
		color = _color;
		outlineThickness = _outlineThickness;
		outlineColor = _outlineColor;
	}
};

struct AllButtonData
{
	ButtonData pressedData;
	ButtonData heldData;
	ButtonData releasedData;
	ButtonData hoveredData;
	ButtonData unhoveredData;

public:
	AllButtonData(const ButtonData& _pressedData = ButtonData(Color::White, 3.0f, Color::Red),
				  const ButtonData& _heldData = ButtonData(Color::White, 3.0f, Color::Red),
				  const ButtonData& _releasedData = ButtonData(Color::White, 3.0f, Color::Red),
				  const ButtonData& _hoveredData = ButtonData(Color::White, 3.0f, Color::Red),
				  const ButtonData& _unhoveredData = ButtonData(Color::White, 3.0f, Color::Red))
	{
		pressedData = _pressedData;
		heldData = _heldData;
		releasedData = _releasedData;
		hoveredData = _hoveredData;
		unhoveredData = _unhoveredData;
	}
};

class Button : public Widget
{
	Widget* foreground;
	function<void()> callback;
	AllButtonData allData;
	bool isSelected;
	bool isHeld;

public:
	void SetForeground(Widget* _foreground)
	{
		foreground = _foreground;
	}
	Widget* GetForeground() const
	{
		return foreground;
	}

public:
	Button(const ObjectData& _data, const AllButtonData& _buttonData = AllButtonData());

private:
	void OnPressed();
	void OnHeld();
	void OnReleased();
	void OnHovered();
	void OnUnhovered();
};