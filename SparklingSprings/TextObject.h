#pragma once
#include "Object.h"

class TextObject : public Object
{
protected:
	Text* text;

public:
	virtual Text* GetDrawable() const override
	{
		return text;
	}
	Vector2f GetShapePosition() const
	{
		if (!text) return Vector2f();
		return text->getPosition();
	}
	Vector2f GetShapeSize() const
	{
		if (!text) return Vector2f();
		return text->getGlobalBounds().getSize();
	}

public:
	TextObject(const TextData& _data);
};