#include "Tile.h"
#include "Macro.h"

Tile::Tile(const string& _name,const TileType& _type, const Vector2f& _position, const Vector2f& _size) : Actor(_name,{ _position, _size, GetPathWithType(_type)})
{
	type = _type;
	SetColorWithType();
	shape->setOutlineThickness(-1.f);
	shape->setFillColor(color);
}
