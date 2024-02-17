#pragma once
#include "Widget.h"
#include <functional>

class Skill : public Widget
{
	bool isUnlocked;
	int cost;
	function<void()> callback;

public:
	Skill(const ObjectData& _data, const int _cost,
		const function<void()>& _callback, const bool _isUnlocked = false);

public:
	void Unlock();
	void Use();
};