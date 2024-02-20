#pragma once
#include "Actor.h"
#include <functional>

using namespace std;

class InteractableActor : public Actor
{
protected:
	function<void()> callback;

public:
	InteractableActor(const string& _name, const ShapeData& _data, 
					  const function<void()>& _callback);

private:
	virtual void Register() override;

public:
	void Interact();
};