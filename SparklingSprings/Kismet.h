#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

struct HitInfo
{
	Vector2f position;
	float distance;
};

bool Raycast(const Vector2f& _origin, const Vector2f& _direction, const float _maxDistance,
			 HitInfo& _hitInfo, const float _precision = 0.01f);
vector<HitInfo> RaycastAll(const Vector2f& _origin, const Vector2f& _direction, const float _maxDistance,
			 HitInfo& _hitInfo, const float _precision = 0.01f);