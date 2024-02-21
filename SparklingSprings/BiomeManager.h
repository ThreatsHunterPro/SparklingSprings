#pragma once
#include "Singleton.h"
#include "IManager.h"
#include "Biome.h"
#include "Macro.h"

class BiomeManager : public Singleton<BiomeManager>, public IManager<string, Biome>
{
	vector<Tile*> tiles;

public:
	void SetTiles(const vector<Tile*>& _tiles)
	{
		tiles = _tiles;
	}
	Tile* GetTileByPosition(const Vector2f& _position) const
	{
		for (Tile* _tile : tiles)
		{
			if (Distance(_tile->GetShapePosition(), _position) <= 1.0f)
			{
				return _tile;
			}
		}

		return nullptr;
	}
	bool CheckAroundTile(const Vector2f& _position, const Vector2i& _range, const Vector2f& _tileSize)
	{
		for (int _rowIndex = 0; _rowIndex < _range.y; _rowIndex++)
		{
			for (int _columnIndex = 0; _columnIndex < _range.x; _columnIndex++)
			{
				const float _targetX = _position.x + _columnIndex * _tileSize.x;
				const float _targetY = _position.y + _rowIndex * _tileSize.y;

				if (Tile* _tile = GetTileByPosition(Vector2f(_targetX, _targetY)))
				{
					if (_tile->GetType() == TT_NONE) continue;
					return false;
				}
			}
		}

		return true;
	}
};