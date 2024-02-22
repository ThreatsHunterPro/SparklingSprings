#pragma once
#include "Stat.h"

class IDamagable
{
	Stat* health;
	Shape* shape;

protected:
	void SetStat(Stat* _stat)
	{
		health = _stat;
	}
public:
	Shape* GetShape() const
	{
		return shape;
	}

public:
	IDamagable(Shape* _shape);

private:
	void Register();

public:
	void TakeDamages(const float _damages)
	{
		if (!health)
		{
			cerr << "Tu as oublié de définir la HealthBar de ton IDamagable !" << endl;
			return;
		}

		health->Update(-_damages);
	}
};