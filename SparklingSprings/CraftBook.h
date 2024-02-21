#pragma once
#include "Singleton.h"
#include "IManager.h"
#include "Canvas.h"
#include "Craft.h"
#include "Button.h"


class CraftBook : public IManager<int, Craft>
{
	Canvas* canvas;
	Vector2f cellSize;
	vector<CraftInfo> craftInfos;
	
public:
	CraftBook();
private:
	void Init();
public:
	void Toggle()
	{
		canvas->SetVisibilityStatus(canvas->IsVisible() ? false : true);
	}

};