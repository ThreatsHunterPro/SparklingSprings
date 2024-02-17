#pragma once
#include "Tile.h"
class Biome
{
	vector<vector<Tile*>> tiles;
	Vector2f startPosition;
	Vector2f tilesSize;
	Vector2f tileCount;
	string tilePath;

public:
	vector<vector<Tile*>> GetTiles() const 
	{ 
		return tiles; 
	};

public:
	Biome(const Vector2f& _startPosition,const Vector2f& _tilesSize,const string& _tilePath);

public:
	void InitBiome();
	void Draw(RenderWindow& _window);

	void CreateSecurityZone();
};

