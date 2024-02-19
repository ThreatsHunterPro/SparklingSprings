#pragma once
#include "Actor.h"
#include "IManagable.h"
#include <iostream>

using namespace std;

enum TileType
{
	TT_NONE, TT_GRASS, TT_ICE, TT_LAVA, TT_SAND,TT_STONE,TT_SIZE
};

class Tile : public Actor
{
	TileType type;

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

		shape->setFillColor(_colors[type]);
	}

	void SetType(const TileType& _type)
	{
		type = _type;
		if (_type != TT_NONE)
		{
			cout << "c'est good";
		}
		SetColorWithType();
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