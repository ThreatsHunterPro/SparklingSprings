#include "Map.h"
#include "BiomeManager.h"

Map::Map()
{
	position = Vector2f(0.0f, 0.0f);
	size = Vector2i(100, 100);
	tileSize = Vector2f(25.0f, 25.0f);

	biomeCount = 5;
	biomeSizeMinMax = {
		Vector2i(5, 5),
		Vector2i(20, 20), //size
	};
	securityZoneSizeMinMax = {
		Vector2i(3, 3),
		Vector2i(10, 10),
	};
}


void Map::InitBackgroundTiles()
{
	vector<Tile*> _tiles;

	for (int _rowIndex = 0; _rowIndex < size.y; _rowIndex++)
	{
		for (int _columnIndex = 0; _columnIndex < size.x; _columnIndex++)
		{
			const float _posX = _columnIndex * tileSize.x;
			const float _posY = _rowIndex * tileSize.y;

			_tiles.push_back(new Tile(position + Vector2f(_posX, _posY), tileSize, TT_NONE));
		}
	}

	BiomeManager::GetInstance().SetTiles(_tiles);
}

void Map::InitBiomes()
{
	for (int _index = 0; _index < biomeCount; _index++)
	{
		const Vector2i& _securityZoneSize = GetRandomSize(securityZoneSizeMinMax);

		Vector2f _biomePosition = Vector2f(0.0f, 0.0f);
		if (!GetValidPosition(_biomePosition, _securityZoneSize))
		{
			cout << "Fail to find valid position !" << endl;
			continue;
		}

		const Vector2i& _biomeSize = GetRandomSize(biomeSizeMinMax);

		Biome* _biome = new Biome(GetRandomType(), _biomeSize, _securityZoneSize);
		_biome->Init(_biomePosition, tileSize);
	}
}

bool Map::GetValidPosition(Vector2f& _position, const Vector2i& _securityZoneSize) const
{
	int _triesCount = 20;

	do
	{
		const float _x = Random(size.x, 0) * tileSize.x;
		const float _y = Random(size.y, 0) * tileSize.y;
		_position = position + Vector2f(_x, _y);
		_triesCount--;

	} while (!BiomeManager::GetInstance().CheckAroundTile(_position, _securityZoneSize, tileSize) && _triesCount > 0);

	return _triesCount > 0;
}


void Map::Init(const Vector2f& _windowSize)
{
	InitBackgroundTiles();
	InitBiomes();
}
