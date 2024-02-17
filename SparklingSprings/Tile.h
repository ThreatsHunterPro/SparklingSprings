#pragma once
#include "Actor.h"

class Tile : public Actor
{
public:
	Tile(const Vector2f& _position, const Vector2f& _size, const string& _path);
};