#pragma once
#include "ShapeWidget.h"
#include <functional>

class Skill : public ShapeWidget
{
	bool isUnlocked;
	int cost;
	function<void()> callback;

public:
	Skill(const ShapeData& _data, const int _cost,
		const function<void()>& _callback, const bool _isUnlocked = false);

public:
	void Unlock();
	void Use();
};