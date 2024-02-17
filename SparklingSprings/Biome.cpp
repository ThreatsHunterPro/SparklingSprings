#include "Biome.h"
#include "Macro.h"
Biome::Biome(const Vector2f& _startPosition, const Vector2f& _tilesSize, const string& _tilePath)
{
	tiles = vector<vector<Tile*>>();
	startPosition = _startPosition;
	tilesSize = _tilesSize;
	tilePath = _tilePath;
	tileCount = Vector2f(Random(25, 5), Random(25, 5));;
	InitBiome();
}

void Biome::InitBiome()
{
	for (int _columnIndex = 0; _columnIndex < tileCount.y; _columnIndex++)
	{
		vector<Tile*> newRow;
		for (int _rowIndex = 0; _rowIndex < tileCount.x; _rowIndex++)
		{
			Tile* _tile = new Tile(Vector2f(int(startPosition.x) + _rowIndex * tilesSize.x, int(startPosition.y) + _columnIndex * tilesSize.y), tilesSize, tilePath);
			newRow.push_back(_tile);
		}
		tiles.push_back(newRow);
	}
	CreateSecurityZone();
}

void Biome::Draw(RenderWindow& _window)
{

	for (int _columnIndex = 0; _columnIndex < tiles.size(); _columnIndex++)
	{
		for (int _rowIndex = 0; _rowIndex < tiles[_columnIndex].size(); _rowIndex++)
		{
			_window.draw(*tiles[_columnIndex][_rowIndex]->GetShape());
		}
	}
}

void Biome::CreateSecurityZone()
{
	RectangleShape* _securityZone = new RectangleShape(tilesSize * 5.f);
	_securityZone->setOrigin(tilesSize * 5.f / 2.f);
	_securityZone->setPosition(tiles[tileCount.y / 2][tileCount.x / 2]->GetShapePosition());
}
