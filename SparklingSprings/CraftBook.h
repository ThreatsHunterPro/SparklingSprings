#pragma once
#include "Singleton.h"
#include "IManager.h"
#include "Craft.h"
#include "Button.h"

class CraftBook : public IManager<int, Craft>
{
	Canvas* canvas;
	Vector2f cellSize;
	vector<Button*> buttons;

public:
	CraftBook();

private:
	void Init();
public:
	void Toggle()
	{
		canvas->SetVisibilityStatus(canvas->IsVisible() ? false : true);
	}
	void BuildHovered();
	void BuildSelected();

};