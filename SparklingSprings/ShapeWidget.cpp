#include "ShapeWidget.h"

ShapeWidget::ShapeWidget(const ShapeData& _data)
{
	shapeObject = new ShapeObject(_data);
}