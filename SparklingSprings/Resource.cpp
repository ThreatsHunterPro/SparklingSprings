#include "Resource.h"

Resource::Resource(const InteractableData& _interactableData, const ResourceData& _data)
				 : InteractableActor(_interactableData)
{
	data = _data;
}