#pragma once
#include "Object.h"

class Widget
{
	bool isVisible;
	int layer;

public:
	void SetVisible(const bool _status)
	{
		isVisible = _status;
	}
	bool IsVisible() const
	{
		return isVisible;
	}

	const int GetLayer() const
	{
		return layer;
	}

	virtual Object* GetObject() const = 0;
	virtual Drawable* GetDrawable() const = 0;

public:
	Widget(const int _layer);
	virtual ~Widget() {}
};