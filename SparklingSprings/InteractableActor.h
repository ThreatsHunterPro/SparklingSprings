#pragma once
#include "Actor.h"
#include <functional>

using namespace std;

struct InteractableData
{
	string name;
	ShapeData data;
	function<void()> callback;

	InteractableData(const string& _name, const ShapeData& _data,
					 const function<void()>& _callback)
	{
		name = _name;
		data = _data;
		callback = _callback;
	}
};

class InteractableActor : public Actor
{
protected:
	function<void()> callback;

public:
	InteractableActor(const InteractableData& _data);

private:
	virtual void Register() override;

public:
	void Interact();
};