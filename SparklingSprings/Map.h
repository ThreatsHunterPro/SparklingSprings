#pragma once
#include "Biome.h"

class Map
{
	vector<Biome*> biomes;
	Vector2f startPosition;
	Vector2f tilesSize;
	string path;

public:
	Map(const Vector2f& _startPosition,const Vector2f& _tilesSize,const string& _path,const int _biomeCount);

public:
	void InitBiomes(const int _biomeCount);

public:
	void Draw(RenderWindow& _window);
};

