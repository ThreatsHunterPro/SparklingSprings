#include "ActionMap.h"
#include "InputManager.h"

ActionMap::ActionMap(const string& _name, const vector<ActionData>& _actionsData) : IManagable(_name)
{
	Register();

	for (const ActionData& _actionData : _actionsData)
	{
		actions.push_back(new Action(_actionData, id));
	}
}

void ActionMap::Register()
{
	InputManager::GetInstance().Add(id, this);
}

void ActionMap::Update(const Event& _event)
{
	for (const auto& _pair : allValues)
	{
		for (const InputData& _inputData : _pair.second->data.keys)
		{
			if (_event.type == _inputData.type && _event.key.code == _inputData.key)
			{
				_pair.second->Execute();
			}
		}
	}

	GarbageValues();
}