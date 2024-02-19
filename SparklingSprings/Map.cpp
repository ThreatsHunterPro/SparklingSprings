#include "Map.h"
#include "BiomeManager.h"

Map::Map(const int _biomeCount,const Vector2f& _windowSize)
{
	biomeCount = _biomeCount;
	BiomeManager::GetInstance().InitBackgroundTiles({0.f,0.f},{25,25},{50,50});
	CreateMap(_windowSize);
}

void Map::CreateMap(const Vector2f& _windowSize)
{
	const Vector2i& _tilesSize = { 25,25 };	
	for (int _index = 0; _index < biomeCount; _index++)
	{
		const Vector2i& _biomeSize = GetRandomBiomeSize();
		const Vector2f& _biomePosition = GetValidPosition(_biomeSize, _windowSize);
		new Biome(GetRandomType(), _biomePosition, _tilesSize, _biomeSize,5);
	}
}
