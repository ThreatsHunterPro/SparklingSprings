#pragma once
#include <iostream>
#include "Timer.h"
#include "ProgressBar.h"

using namespace std;

struct Stat
{
	ProgressBar* bar;
	float maxValueUpgradeFactor;

	Stat() = default;
	Stat(const float _valueFactor, ProgressBar* _bar)
	{
		bar = _bar;
		maxValueUpgradeFactor = 0.3f;
	}

	virtual void Update(const float _value)
	{
		bar->ChangeValue(_value);
	}

	void Reset()
	{
		bar->ResetValue();
	}

	virtual void Upgrade()
	{
		bar->ChangeMaxValue(maxValueUpgradeFactor);
	}
};

struct ChangingStat : public Stat
{
	float valueFactor;
	float rate;
	Timer* updateTimer;
	float valueFactorUpgradeFactor;
	float rateUpgradeFactor;

	float GetCurrentValue() const
	{
		return bar->GetCurrentValue();
	}

	ChangingStat(const float _valueFactor, ProgressBar* _bar)
				: Stat(_valueFactor, _bar)
	{
		valueFactor = _valueFactor;
		rate = 0.01f;
		updateTimer = StartUpdateTimer();
		valueFactorUpgradeFactor = 0.3f;
		rateUpgradeFactor = 0.3f;
	}

	Timer* StartUpdateTimer()
	{
		return new Timer(this, &ChangingStat::Update, seconds(rate), true, true, valueFactor);
	}

	virtual void Update(const float _value) override
	{
		Stat::Update(_value);
	}

	virtual void Upgrade() override
	{
		updateTimer->Stop();

		Stat::Upgrade();
		valueFactor += valueFactor * valueFactorUpgradeFactor;
		rate += rate * rateUpgradeFactor;

		updateTimer = StartUpdateTimer();
	}
};