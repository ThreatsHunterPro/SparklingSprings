#pragma once
#include "Widget.h"
#include "Object.h"

enum ProgressType
{
	PT_CENTER,
	PT_LEFT,
	PT_TOP,
	PT_RIGHT,
	PT_BOTTOM
};

class ProgressBar : public Widget
{
	ProgressType type;
	Widget* foreground;
	float maxValue;
	float currentValue;

public:
	void SetValue(const float _newValue)
	{
		currentValue = _newValue > maxValue ? maxValue : _newValue < 0 ? 0 : _newValue;
		Update();
	}
	void ChangeValue(const float _byAmount)
	{
		const float _newValue = currentValue + _byAmount;
		currentValue = _newValue > maxValue ? maxValue : _newValue < 0 ? 0 : _newValue;
		Update();
	}

public:
	ProgressBar(const ObjectData& _data, Canvas* _canvas, const string& _path,
				const ProgressType& _type, const float _maxValue = 100.0f);
	~ProgressBar();

private:
	void Update();
	void UpdateOriginAndPosition(const Vector2f& _size);
	IntRect MakeRect(const float _percent);
};