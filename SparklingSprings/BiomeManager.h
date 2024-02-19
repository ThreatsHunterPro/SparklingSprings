#pragma once
#include "Singleton.h"
#include "IManager.h"
#include "Biome.h"

class BiomeManager : public Singleton<BiomeManager> , public IManager<string, Biome>
{
	vector<Tile*> backgroundTiles;

public:
	void InitBackgroundTiles(const Vector2f& _position, const Vector2f& _size,const Vector2i& _tilesCount);

public:
	Tile* GetTileByPosition(const Vector2f& _position) const
	{
		for (Tile* _tile : backgroundTiles)
		{
			if (Vector2i(_tile->GetShapePosition()) == Vector2i(_position))
			{
				return _tile;
			}
		}
		return nullptr;
	}
};

