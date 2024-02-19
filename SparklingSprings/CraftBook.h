#pragma once
#include "Singleton.h"
#include "IManager.h"
#include "Canvas.h"
#include "Craft.h"

class CraftBook : public Singleton<CraftBook>, public IManager<int, Craft>
{
	Canvas* canvas;

public:
	CraftBook() = default;
	CraftBook(Canvas* _canvas);

public:
	void Toggle()
	{
		canvas->SetVisibilityStatus(canvas->IsVisible() ? false : true);
	}
};