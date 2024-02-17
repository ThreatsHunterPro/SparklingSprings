#pragma once
#include "Object.h"
#include "Canvas.h"
#include <iostream>

using namespace std;

class Widget : public Object
{
	bool isVisible;

public:
	void SetVisible(const bool _status)
	{
		isVisible = _status;
	}
	bool IsVisible() const
	{
		return isVisible;
	}

public:
	Widget(const ObjectData& _data);
};