#pragma once
#include "Biome.h"
#include "Macro.h"

class Map
{
	int biomeCount;
public:
	Map(const int _biomeCount, const Vector2f& _windowSize);

public:
	TileType GetRandomType() const
	{

		return static_cast<TileType>(Random(TT_SIZE,0));
	}

	Vector2i GetRandomBiomeSize() const
	{
		return Vector2i(Random(25, 5), Random(25, 5));
	}

	Vector2f GetValidPosition(const Vector2i _biomeSize, const Vector2f& _windowSize) const
	{
		const int _x = Random(_biomeSize.x);
		const int _y = Random(_biomeSize.y);
		bool _isValid = false;

		return Vector2f(100.f,100.f);
	}


public:
	void CreateMap(const Vector2f& _windowSize);
};

