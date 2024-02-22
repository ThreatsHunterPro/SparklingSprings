#include "Resource.h"

Resource::Resource(const string& _name, const ShapeData& _shapeData, const ResourceData& _data,
				   const function<void()>& _callback) 
				 : Actor(_name, _shapeData), IInteractable(GetDrawable(), _callback)
{
	data = _data;
}