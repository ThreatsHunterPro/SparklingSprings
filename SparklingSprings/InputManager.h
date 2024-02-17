#pragma once
#include "Singleton.h"
#include "IManager.h"
#include "ActionMap.h"

class InputManager : public Singleton<InputManager>, public IManager<string, ActionMap>
{
	Vector2f mousePosition;

public:
	Vector2f GetMousePosition() const 
	{
		return mousePosition;
	}

public:
	bool Update(RenderWindow& _window);

private:
	void UpdateInputs(const Event& _event);
};