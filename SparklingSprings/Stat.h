#pragma once
#include <iostream>
#include "Timer.h"
#include "ProgressBar.h"

using namespace std;

struct Stat
{
	float valueFactor;
	float rate;
	ProgressBar* bar;
	Timer* updateTimer;

	float maxValueUpgradeFactor;
	float valueFactorUpgradeFactor;
	float rateUpgradeFactor;

	Stat() = default;
	Stat(const float _valueFactor, ProgressBar* _bar)
	{
		valueFactor = _valueFactor;
		rate = 0.01f;
		bar = _bar;
		updateTimer = StartUpdateTimer();
		maxValueUpgradeFactor = 0.3f;
		valueFactorUpgradeFactor = 0.3f;
		rateUpgradeFactor = 0.3f;
	}

	Timer* StartUpdateTimer()
	{
		return new Timer(this, &Stat::Update, seconds(rate), true, true, valueFactor);
	}

	void Update(const float _value)
	{
		bar->ChangeValue(_value);
	}

	void Reset()
	{
		bar->ResetValue();
	}

	void Upgrade()
	{
		updateTimer->Stop();

		bar->ChangeMaxValue(maxValueUpgradeFactor);
		valueFactor += valueFactor * valueFactorUpgradeFactor;
		rate += rate * rateUpgradeFactor;

		updateTimer = StartUpdateTimer();
	}
};