#pragma once
#include "Actor.h"
#include <functional>

using namespace std;

class IInteractable
{
	Shape* shape;
	function<void()> callback;

public:
	Shape* GetShape() const
	{
		return shape;
	}

public:
	IInteractable(Shape* _shape, const function<void()>& _callback);

public:
	void Interact();
};