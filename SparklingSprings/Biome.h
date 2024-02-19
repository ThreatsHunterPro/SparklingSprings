#pragma once
#include "Tile.h"
#include "IManagable.h"


class Biome : public IManagable<string>
{
	vector<vector<Tile*>> biome;
	int securityZoneSize;

public:
	Biome(const TileType& _type, const Vector2f& _position, const Vector2i& _size,const Vector2i& _biomeSize,const int _securityZone);

	void InitBiome(const TileType& _type, const Vector2f& _position, const Vector2f& _size, const Vector2i& _biomeSize);

	// Hérité via IManagable
	void Register() override;
};

