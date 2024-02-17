#include "Skill.h"

Skill::Skill(const ObjectData& _data, const int _cost,
			 const function<void()>& _callback, const bool _isUnlocked)
			 : Widget(_data)
{
	isUnlocked = _isUnlocked;
	cost = _cost;
	callback = _callback;
}

void Skill::Unlock()
{
	isUnlocked = true;
}

void Skill::Use()
{
	if (!isUnlocked)
	{
		cout << "Vous n'avez pas encore débloqué cette aptitude !" << endl;
		return;
	}

	if (callback)
	{
		callback();
	}
}