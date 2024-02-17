#include "Macro.h"

int GetUniqueID()
{
	static int _id;
	return ++_id;
}

float Length(const Vector2f& _vector)
{
	return static_cast<float>(sqrtf(pow(_vector.x, 2.0f) + pow(_vector.y, 2.0f)));
}

float Distance(const Vector2f& _first, const Vector2f& _second)
{
	return Length(_second - _first);
}

void Normalize(Vector2f& _vector)
{
	_vector /= Length(_vector);
}