#include "BiomeManager.h"
#include "Macro.h"
void BiomeManager::InitBackgroundTiles(const Vector2f& _position, const Vector2f& _size, const Vector2i& _tilesCount)
{
	for (int _rowIndex = 0; _rowIndex < _tilesCount.y; _rowIndex++)
	{
		for (int _columnIndex = 0; _columnIndex < _tilesCount.x; _columnIndex++)
		{

			const float _posX = _columnIndex * _size.x;
			const float _posY = _rowIndex * _size.y;

			backgroundTiles.push_back(new Tile(STRING_ID("BgTile"), TT_NONE, _position + Vector2f(_posX,_posY),_size));
		}
	}
}
