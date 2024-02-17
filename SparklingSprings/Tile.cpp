#include "Tile.h"
#include "Macro.h"
Tile::Tile(const Vector2f& _position, const Vector2f& _size, const string& _path)
	: Object({_position,_size,_path})
{
	objects = vector<Object*>();
	shape->setOutlineThickness(1.f);
	shape->setOutlineColor(Color::Red);
}