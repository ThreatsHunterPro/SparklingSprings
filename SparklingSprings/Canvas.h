#pragma once
#include "IManagable.h"
#include <SFML/Graphics.hpp>
#include <string>

using namespace std;
using namespace sf;

class Widget;

class Canvas : public IManagable<string>
{
	bool isVisible;
	FloatRect rect;
	vector<Widget*> widgets;

public:
	void SetVisibilityStatus(const bool _status)
	{
		isVisible = _status;
	}
	void AddWidget(Widget* _widget)
	{
		widgets.push_back(_widget);
	}
	bool IsVisible() const
	{
		return isVisible;
	}
	FloatRect GetRect() const
	{
		return rect;
	}
	vector<Widget*> GetWidgets() const
	{
		return widgets;
	}

public:
	Canvas(const string& _name, const FloatRect& _rect, const vector<Widget*>& _widgets = vector<Widget*>());

private:
	virtual void Register() override;
};