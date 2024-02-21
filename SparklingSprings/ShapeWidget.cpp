#include "ShapeWidget.h"

ShapeWidget::ShapeWidget(const ShapeData& _data, const int _layer) :Widget(_layer)
{
	shapeObject = new ShapeObject(_data);
}