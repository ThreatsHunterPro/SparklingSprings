#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;
using namespace sf;

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

template <typename T>
bool Contains(T* _valueToFind, const vector<T*>& _vector)
{
	for (T* _value : _vector)
	{
		if (_value == _valueToFind) return true;
	}

	return false;
}