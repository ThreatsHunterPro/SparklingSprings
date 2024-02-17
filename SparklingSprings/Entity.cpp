#include "Entity.h"
#include "Macro.h"
#include "Component.h"
#include "EntityManager.h"
#include "TimerManager.h"
#include "TextureManager.h"

Entity::Entity(const EntityData& _data) : IManagable(to_string(GetUniqueID()) + _data.name)
{
	Register();

	components = vector<Component*>();
	shape = new RectangleShape(_data.size);
	shape->setPosition(_data.position);
	TextureManager::GetInstance().Load(shape, _data.path);
}

Entity::~Entity()
{
	delete shape;

	for (Component* _component : components)
	{
		delete _component;
	}
}


void Entity::Register()
{
	EntityManager::GetInstance().Add(id, this);
}

void Entity::Update()
{
	const float _deltaTime = TimerManager::GetInstance().GetDeltaTime();
	for (Component* _component : components)
	{
		_component->Update(_deltaTime);
	}
}