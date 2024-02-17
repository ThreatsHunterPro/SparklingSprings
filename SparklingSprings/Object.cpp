#include "Object.h"
#include "TextureManager.h"

Object::Object(const ObjectData& _data)
{
	shape = new RectangleShape(_data.size);
	//shape->setOrigin(_data.size / 2.0f);
	shape->setPosition(_data.position/* + _data.size / 2.0f*/);

	TextureManager& _textureManager = TextureManager::GetInstance();
	_data.rect == IntRect() ? _textureManager.Load(shape, _data.path)
							: _textureManager.LoadWithRect(shape, _data.path, _data.rect);
}