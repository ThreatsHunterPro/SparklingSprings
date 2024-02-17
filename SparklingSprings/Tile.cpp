#include "Tile.h"
#include "Macro.h"

Tile::Tile(const Vector2f& _position, const Vector2f& _size, const string& _path)
	: Actor("Tile" + to_string(GetUniqueID()), ObjectData(_position, _size, _path))
{

}