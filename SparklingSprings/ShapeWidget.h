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

public:
	ShapeWidget(const ShapeData& _data);
};