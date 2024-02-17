#include "Map.h"
#include "Macro.h"
Map::Map(const Vector2f& _startPosition, const Vector2f& _tilesSize, const string& _path, const int _biomeCount)
{
	biomes = vector<Biome*>();
	startPosition = _startPosition;
	tilesSize = _tilesSize;
	path = _path;
	InitBiomes(_biomeCount);
}

void Map::InitBiomes(const int _biomeCount)
{
	for (int i = 0; i < _biomeCount; i++)
	{
		biomes.push_back(new Biome(Vector2f(Random(1000,0), Random(600, 0)), tilesSize, path));
	}

}

void Map::Draw(RenderWindow& _window)
{
	for (int _index = 0; _index < biomes.size(); _index++)
	{
		biomes[_index]->Draw(_window);
	}
}
