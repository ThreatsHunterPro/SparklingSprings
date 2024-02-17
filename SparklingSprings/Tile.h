#pragma once
#include "Object.h"

class Tile : public Object
{
	vector<Object*> objects;

public:
	Tile(const Vector2f& _position, const Vector2f& _size, const string& _path);
};