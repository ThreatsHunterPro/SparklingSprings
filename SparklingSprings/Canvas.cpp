#include "Canvas.h"
#include "Widget.h"
#include "HUD.h"

Canvas::Canvas(const string& _name, const FloatRect& _rect, const vector<Widget*>& _widgets)
				: IManagable(_name)
{
	Register();

	rect = _rect;
	widgets = _widgets;
}

void Canvas::Register()
{
	HUD::GetInstance().Add(id, this);
}