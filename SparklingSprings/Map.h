#pragma once
#include "Biome.h"
#include "Macro.h"

struct MinMax
{
	Vector2i min;
	Vector2i max;
};

class Map
{
	Vector2f position;
	Vector2i size;
	Vector2f tileSize;

	int biomeCount;
	MinMax biomeSizeMinMax;
	MinMax securityZoneSizeMinMax;

private:
	TileType GetRandomType() const
	{
		return static_cast<TileType>(Random<int>(TT_SIZE, 0));
	}

	Vector2i GetRandomSize(const MinMax& _minMax) const
	{
		const int _sizeX = Random(_minMax.max.x, _minMax.min.x);
		const int _sizeY = Random(_minMax.max.y, _minMax.min.y);
		return Vector2i(_sizeX, _sizeY);
	}

public:
	Map();

private:
	void InitBackgroundTiles();
	void InitBiomes();
	bool GetValidPosition(Vector2f& _position, const Vector2i& _securityZoneSize) const;

public:
	void Init(const Vector2f& _windowSize);
};