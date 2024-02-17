#include "InputManager.h"

bool InputManager::Update(RenderWindow& _window)
{
	Event _event;
	while (_window.pollEvent(_event))
	{
		if (_event.type == Event::Closed) return false;

		UpdateInputs(_event);
	}

	mousePosition = Vector2f(Mouse::getPosition(_window));
	GarbageValues();

	return true;
}

void InputManager::UpdateInputs(const Event& _event)
{
	for (const auto& _pair : allValues)
	{
		_pair.second->Update(_event);
	}
}