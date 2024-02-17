#pragma once
#include "Tile.h"
#include "IManagable.h"


class Biome : public IManagable<string>
{
	vector<vector<Tile*>> biome;
	Vector2i securityZoneSize;

public:
	Biome(const TileType& _type, const Vector2f& _position, const Vector2i& _size,const Vector2i& _biomeSize);

	void InitBiome(const TileType& _type, const Vector2f& _position, const Vector2f& _size, const Vector2i& _biomeSize);

	// Hérité via IManagable
	void Register() override;
};

