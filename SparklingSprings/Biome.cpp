#include "Biome.h"
#include "Macro.h"
#include "BiomeManager.h"

Biome::Biome(const TileType& _type, const Vector2f& _position, const Vector2i& _size, const Vector2i& _biomeSize) : IManagable(STRING_ID("Biome"))
{
	biome = vector<vector<Tile*>>();
	const Vector2f& _tileSize = Vector2f(float(_size.x), float(_size.y));
	InitBiome(_type, _position, _tileSize,_biomeSize);
	securityZone = nullptr;
}

void Biome::InitBiome(const TileType& _type, const Vector2f& _position, const Vector2f& _size, const Vector2i& _biomeSize)
{
	const Vector2i& _tilesCount = _biomeSize;

	for (int _y = 0; _y < _tilesCount.y; _y++)
	{
		vector<Tile*> _row;
		for (int _x = 0; _x < _tilesCount.x; _x++)
		{
			const Vector2f& _pos = _position + Vector2f(_x * _size.x, _y * _size.y);
			_row.push_back(new Tile("Tile" + to_string(GetUniqueID()),_type, _pos, _size));
		}
		biome.push_back(_row);
	}

	const Vector2f& _securityZoneSize = _size * 5.f;
	securityZone = new RectangleShape(_securityZoneSize);
	securityZone->setOrigin(_securityZoneSize / 2.0f);
	securityZone->setPosition(biome[_tilesCount.y / 2][_tilesCount.x /2]->GetShapePosition());
}

void Biome::Register()
{
	BiomeManager::GetInstance().Add(id, this);
}
