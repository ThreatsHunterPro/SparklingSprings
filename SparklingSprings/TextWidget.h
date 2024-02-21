#pragma once
#include "Widget.h"
#include "TextObject.h"

class TextWidget : public Widget
{
protected:
	TextObject* textObject;

public:
	virtual TextObject* GetObject() const override
	{
		return textObject;
	}
	virtual Text* GetDrawable() const override
	{
		return textObject->GetDrawable();
	}

	void SetOrigineAtMiddle()
	{
		Text* _text = textObject->GetDrawable();
		_text->setOrigin(_text->getLocalBounds().getSize() / 2.f);
	}

public:
	TextWidget(const TextData& _data,const int _layer);
};