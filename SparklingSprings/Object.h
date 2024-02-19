#pragma once
#include <SFML/Graphics.hpp>
#include <string>

using namespace std;
using namespace sf;

struct Data
{
	Vector2f position;
	string path;

	Data(const Vector2f& _position, const string& _path = "")
	{
		position = _position;
		path = _path;
	}
};

struct ShapeData : public Data
{
	Vector2f size;
	IntRect rect;

	ShapeData() = default;
	ShapeData(const Vector2f& _position, const Vector2f& _size,
		const string& _path = "", const IntRect& _rect = IntRect()) : Data(_position, _path)
	{
		size = _size;
		rect = _rect;
	}
};

struct TextData : public Data
{
	string text;
	int size;
	Color color;

	TextData() = default;
	TextData(const string& _text, const Vector2f& _position, const string& _path = "",
			 const int _size = 16, const Color& _color = Color::White) : Data(_position, _path)
	{
		text = _text;
		size = _size;
		color = _color;
	}
};

class Object
{
public:
	virtual Drawable* GetDrawable() const = 0;

public:
	virtual ~Object() {};
};