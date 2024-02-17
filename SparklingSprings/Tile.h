#pragma once
#include "Actor.h"
#include "IManagable.h"

enum TileType
{
	TT_NONE = -1, TT_GRASS, TT_ICE, TT_LAVA, TT_SAND,TT_STONE,TT_SIZE
};

class Tile : public Actor
{
	TileType type;
	Color color;

public:

	void SetColorWithType()
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

		color = _colors[type + 1];
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

		return _paths[_type + 1];
	}

public:
	Tile(const string& _name, const TileType& _type,const Vector2f& _position, const Vector2f& _size);
};