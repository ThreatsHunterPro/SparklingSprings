#pragma once
#include "Singleton.h"
#include "IManager.h"
#include "Skill.h"
#include "Canvas.h"

class SkillTree : public Singleton<SkillTree>, public IManager<string, Skill>
{
	Canvas* canvas;

public:
	SkillTree() = default;
	SkillTree(Canvas* _canvas);

public:
	void Toggle()
	{
		canvas->SetVisibilityStatus(canvas->IsVisible() ? false : true);
	}
};