#pragma once
#include "IManager.h"
#include "IManagable.h"
#include "Action.h"

struct ActionMap : public IManager<string, Action>, public IManagable<string>
{
	bool isRunning;
	vector<Action*> actions;

public:
	void SetIsRunning(const bool _status)
	{
		isRunning = _status;
	}
	bool IsRunning() const
	{
		return isRunning;
	}

public:
	ActionMap(const string& _name, const vector<ActionData>& _actionsData = vector<ActionData>(), 
			  const bool _isRunning = true);

private:
	virtual void Register() override;

public:
	void Update(const Event& _event);
};