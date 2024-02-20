#pragma once
#include "Stat.h"

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