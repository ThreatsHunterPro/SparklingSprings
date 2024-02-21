#include "Tile.h"
#include "Macro.h"

Tile::Tile(const Vector2f& _position, const Vector2f& _size, const TileType& _type)
		 : Actor("Tile" + to_string(GetUniqueID()), ShapeData(_position, _size, GetPathWithType(_type)))
{
	type = _type;
	SetColorWithType(_type);
	shape->setOutlineThickness(-1.0f);
}