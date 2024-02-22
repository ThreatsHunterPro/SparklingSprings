#include "IInteractable.h"

IInteractable::IInteractable(Shape* _shape, const function<void()>& _callback)
{
	shape = _shape;
	callback = _callback;
}


void IInteractable::Interact()
{
	if (callback)
	{
		callback();
	}
}