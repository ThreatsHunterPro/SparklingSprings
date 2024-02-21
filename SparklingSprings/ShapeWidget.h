#pragma once
#include "Widget.h"
#include "ShapeObject.h"

class ShapeWidget : public Widget
{
protected:
	ShapeObject* shapeObject;

public:
	virtual ShapeObject* GetObject() const override
	{
		return shapeObject;
	}
	virtual Shape* GetDrawable() const override
	{
		return shapeObject->GetDrawable();
	}
	virtual void SetShapePosition(const Vector2f& _position)
	{
		GetDrawable()->setPosition(_position);
	}

	void SetOriginAtMiddle()
	{
		Shape* _shape = shapeObject->GetDrawable();
		_shape->setOrigin(_shape->getGlobalBounds().getSize() / 2.0f);
	}

	void SetColor(const Color& _color)
	{
		Shape* _shape = shapeObject->GetDrawable();
		_shape->setFillColor(_color);
	}

public:
	ShapeWidget(const ShapeData& _data, const int _layer);
};