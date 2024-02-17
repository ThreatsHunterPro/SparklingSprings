#include "ProgressBar.h"
#include "Widget.h"
#include "TextureManager.h"
#include "HUD.h"

ProgressBar::ProgressBar(const ObjectData& _data, Canvas* _canvas, const string& _path,
                         const ProgressType& _type, const float _maxValue)
                       : Widget(_data)
{
    type = _type;
    foreground = new Widget(ObjectData(_data.position, _data.size, _path));
    _canvas->AddWidget(foreground);

    UpdateOriginAndPosition(_data.size);

    maxValue = _maxValue;
    currentValue = maxValue;
}

ProgressBar::~ProgressBar()
{
    delete foreground;
}


void ProgressBar::UpdateOriginAndPosition(const Vector2f& _size)
{
	Shape* _fgShape = foreground->GetShape();
    const Vector2f& _barPosition = GetShapePosition();

    if (type == PT_CENTER)
    {
        _fgShape->setOrigin(_size / 2.0f);
        shape->setOrigin(_size / 2.0f);
    }
    else if (type == PT_RIGHT)
    {
        _fgShape->setOrigin(_size.x, 0);
        shape->setOrigin(_size.x, 0);
        _fgShape->setPosition(_barPosition + Vector2f(_size.x, 0.0f));
        shape->setPosition(_barPosition + Vector2f(_size.x, 0.0f));
    }
    else if (type == PT_BOTTOM)
    {
        _fgShape->setOrigin(0, _size.y);
        shape->setOrigin(0, _size.y);
        _fgShape->setPosition(_barPosition + Vector2f(0.0f, _size.y));
        shape->setPosition(_barPosition + Vector2f(0.0f, _size.y));
    }
}

IntRect ProgressBar::MakeRect(const float _percent)
{
    const Texture* _bgTexture = shape->getTexture();
    const Vector2f& _textureSize = Vector2f(_bgTexture->getSize());
    FloatRect _rect;

    if (type == PT_CENTER)
    {
        _rect.left = (_textureSize.x - _percent * _textureSize.x) / 2.0f;
        _rect.top = (_textureSize.x - _percent * _textureSize.x) / 2.0f;
        _rect.width = _percent * _textureSize.x;
        _rect.height = _percent * _textureSize.y;
    }
    else if (type == PT_LEFT || type == PT_TOP)
    {
        _rect.top = 0.0f;
        _rect.left = 0.0f;
        _rect.height = _textureSize.y * (type == PT_TOP ? _percent : 1.0f);
        _rect.width = _textureSize.x * (type == PT_LEFT ? _percent : 1.0f);
    }
    else if (type == PT_RIGHT)
    {
        _rect.top = 0.0f;
        _rect.height = _textureSize.y;
        _rect.left = _textureSize.x - _percent * _textureSize.x;
        _rect.width = _percent * _textureSize.x;
    }
    else if (type == PT_BOTTOM)
    {
        _rect.top = _textureSize.y - _percent * _textureSize.y;
        _rect.height = _percent * _textureSize.y;
        _rect.left = 0.0f;
        _rect.width = _textureSize.x;
    }
    return IntRect(_rect);
}

void ProgressBar::Update()
{
    Shape* _fgShape = foreground->GetShape();

    const float _fillPercent = currentValue / maxValue;
    const IntRect& _rect = MakeRect(_fillPercent);
    _fgShape->setTextureRect(_rect);

    Vector2i _directions[] = {
        Vector2i(1, 1),
        Vector2i(1, 0),
        Vector2i(0, 1),
        Vector2i(1, 0),
        Vector2i(0, 1),
    };

    Vector2f _scale = _fgShape->getScale();
    if (_directions[type].x) _scale.x = _fillPercent;
    if (_directions[type].y) _scale.y = _fillPercent;
    _fgShape->setScale(_scale);
}