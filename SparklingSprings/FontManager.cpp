#include "FontManager.h"
#include <iostream>

FontManager::FontManager()
{
	ResetAlpha();
}


void FontManager::Fade(const vector<Text*>& _texts, const string& _path, const Color& _targetColor)
{
	currentAlpha += alphaFactor;

	if (alphaFactor > 0 && currentAlpha >= 255)
	{
		fadeTimer->Stop();
		ResetAlpha();
		for (Text* _text : _texts)
		{
			Load(_text, _path);
		}
	}

	if (alphaFactor < 0 && currentAlpha <= 30)
	{
		// texts apres => 0 -> 255
		for (Text* _text : _texts)
		{
			_text->setFillColor(_targetColor);
			Load(_text, _path);
		}
		alphaFactor = 1;
		currentAlpha = 0;
	}

	else
	{
		// texts avant => 255 -> 0
		for (Text* _text : _texts)
		{
			Color _color = _text->getFillColor();
			_color.a = currentAlpha;
			_text->setFillColor(_color);
		}
	}
}

void FontManager::ResetAlpha()
{
	fadeTimer = nullptr;
	currentAlpha = 255;
	alphaFactor = -1;
}


void FontManager::Load(Text* _text, const string& _path, const bool _smooth)
{
	FontData* _fontData = Get(_path);

	if (!_fontData)
	{
		_fontData = new FontData(_path);
		if (!_fontData->loadFromFile("Assets/Fonts/" + _path))
		{
			cerr << "La police d'�criture n'a pas �t� correctement charg�e !" << endl;
		}

		_fontData->setSmooth(_smooth);
	}

	_text->setFont(*_fontData);
}

void FontManager::LoadWithFade(const vector<Text*>& _texts, const string& _path, const float _duration, const Color& _targetColor)
{
	if (fadeTimer) return;

	alphaFactor = -1;
	const function<void()>& _callback = [this, _texts, _path, _targetColor]() { Fade(_texts, _path, _targetColor); };
	fadeTimer = new Timer(_callback, seconds(_duration / (255 * 2)), true, true);
}