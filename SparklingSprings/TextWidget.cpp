#include "TextWidget.h"
#include "FontManager.h"

TextWidget::TextWidget(const TextData& _data, const int _layer) : Widget(_layer)
{
	textObject = new TextObject(_data);
}