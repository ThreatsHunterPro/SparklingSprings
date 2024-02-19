#pragma once
#include "Object.h"

class ShapeObject : public Object
{
protected:
	Shape* shape;

public:
	virtual Shape* GetDrawable() const override
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
	ShapeObject(const ShapeData& _data);
};