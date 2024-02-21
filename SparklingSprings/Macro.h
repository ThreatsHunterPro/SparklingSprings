#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;
using namespace sf;

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

#define STRING_ID(name) name + to_string(GetUniqueID())
#define SIZE(vector) static_cast<int>(vector.size())

int GetUniqueID();

int Random(const int _max, const int _min = 0);

template <typename T>
bool IsEqual(const T& _first, const T& _second, const float _minRange = 0.001f)
{
	return abs(_second - _first) <= _minRange;
}

float Length(Vector2f& _vector);

void Normalize(Vector2f& _vector);

float Distance(const Vector2f& _first, const Vector2f& _second);

template<typename T>
void Sort(vector<T>& _vector)
{
	const int _tempCount = (const int)_vector.size();
	for (int _index = 0; _index < _tempCount; _index++)
	{
		const int _layer = _vector[_index]->GetLayer();
		int _currentIndex = _index;
		while (_currentIndex > 0 && _vector[_currentIndex - 1]->GetLayer() > _layer)
		{
			_vector[_currentIndex] = _vector[_currentIndex - 1];
			_currentIndex--;
		}
		_vector[_currentIndex] = _vector[_index];
	}
}

