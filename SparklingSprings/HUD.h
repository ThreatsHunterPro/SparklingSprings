#pragma once
#include "Singleton.h"
#include "IManager.h"
#include "Canvas.h"
#include "Button.h"

class HUD : public Singleton<HUD>, public IManager<string, Canvas>
{
	vector<Button*> buttons;
	vector<Widget*> widgets;

public:
	void AddButton(Button* _button)
	{
		buttons.push_back(_button);
	}

	vector<Widget*> GetAllWidgets() 
	{
		vector<Widget*> _widgets;

		for (Canvas* _canvas : GetAllValues())
		{
			if (!_canvas->IsVisible()) continue;
			for (Widget* _widget : _canvas->GetWidgets())
			{
				if (!_widget->IsVisible()) continue;
				_widgets.push_back(_widget);
			}
		}

		return _widgets;
	}

public:
	void Interact(const Vector2f& _worldPosition, const Event::EventType& _type);
};