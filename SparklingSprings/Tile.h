#pragma once
#include "Actor.h"
#include "IManagable.h"
#include <iostream>

using namespace std;

enum TileType
{
	TT_NONE,
	TT_GRASS,
	TT_ICE,
	TT_LAVA,
	TT_SAND,
	TT_STONE,
	TT_SIZE
};

class Tile : public Actor
{
	TileType type;

public:
	void SetColorWithType(const TileType& _type)
	{
		vector<Color> _colors =
		{
			Color::Cyan,
			Color::Green,
			Color::Blue,
			Color(255, 165, 0,255),
			Color(244,164,96,255),
			Color(128,128,128,255),
		};

		shape->setFillColor(_colors[_type]);
	}
	string GetPathWithType(const TileType& _type) const
	{
		vector<string> _paths =
		{
			" ",
			" ",
			" ",
			" ",
			" ",
			" ",
		};

		return _paths[_type];
	}
	TileType GetType() const
	{
		return type;
	}

public:
	Tile(const Vector2f& _position, const Vector2f& _size, const TileType& _type);
};