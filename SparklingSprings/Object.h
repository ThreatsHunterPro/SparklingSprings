#pragma once
#include <SFML/Graphics.hpp>
#include <string>

using namespace std;
using namespace sf;

struct ObjectData
{
	Vector2f position;
	Vector2f size;
	string path;
	IntRect rect;

	ObjectData() = default;
	ObjectData(const Vector2f& _position, const Vector2f& _size,
		const string& _path = "", const IntRect& _rect = IntRect())
	{
		position = _position;
		size = _size;
		path = _path;
		rect = _rect;
	}
};

class Object
{
protected:
	Shape* shape;

public:
	Shape* GetShape() const
	{
		return shape;
	}
	Vector2f GetShapePosition() const
	{
		if (!shape) return Vector2f();
		return shape->getPosition();
	}
	Vector2f GetShapeSize() const
	{
		if (!shape) return Vector2f();
		return shape->getGlobalBounds().getSize();
	}

public:
	Object(const ObjectData& _data);
};