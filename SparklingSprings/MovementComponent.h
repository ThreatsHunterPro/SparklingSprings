#pragma once
#include "Component.h"
#include <SFML/Graphics.hpp>
#include <functional>

using namespace std;
using namespace sf;

class MovementComponent : public Component
{
	bool canMove;
	float speed;
	float minRange;
	Vector2f destination;
	function<void()> callback;

public:
	void SetCanMove(const bool _status)
	{
		canMove = _status;
	}
	void SetDestinationA(const Vector2f& _destination) {}
	void SetDestination(const Vector2f& _destination, const bool _canMove = true)
	{
		destination = _destination;
		canMove = _canMove;
	}
	void SetCallback(const function<void()>& _callback)
	{
		callback = _callback;
	}

public:
	MovementComponent(Actor* _owner);

private:
	void MoveToDestination(const float _deltaTime);
	bool IsAtPosition() const;

public:
	virtual void Update(const float _deltaTime) override;
};