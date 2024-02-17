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
		bar->ChangeMaxValue(maxValueUpgradeFactor);
		valueFactor += valueFactor * valueFactorUpgradeFactor;

		updateTimer->Stop();
		rate += rate * rateUpgradeFactor;
		updateTimer = StartUpdateTimer();
	}
};

struct PlayerStats
{
	Stat* health;
	float regenCooldown;
	Stat* mana;
	Stat* thirst;
	Stat* hunger;

	PlayerStats(ProgressBar* _healthBar, ProgressBar* _manaBar,
				ProgressBar* _thirstBar, ProgressBar* _hungerBar)
	{
		health = new Stat(1.0f, _healthBar);
		regenCooldown = 3.0f;
		mana = new Stat(0.5f, _manaBar);
		thirst = new Stat(-1.0f, _thirstBar);
		hunger = new Stat(-0.3f, _hungerBar);
	}

	void TakeDamages(const float _damages)
	{
		health->Update(_damages);
	}

	void UseMana(const float _mana)
	{
		mana->Update(_mana);
	}

	void Drink(const float _water)
	{
		thirst->Update(_water);
	}

	void Eat(const float _food)
	{
		hunger->Update(_food);
	}

	void StopHealthRegen()
	{
		if (!health->updateTimer) return;

		health->updateTimer->Stop();
		new Timer([this]()
		{
			health->updateTimer = health->StartUpdateTimer();
		}, seconds(regenCooldown));
	}
};