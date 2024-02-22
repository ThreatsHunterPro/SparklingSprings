#pragma once
#include "Macro.h"

class Actor;

struct HitInfo
{
	Vector2f position;
	float distance;
	Actor* actor;
};

bool Raycast(const Vector2f& _origin, const Vector2f& _direction, const float _maxDistance,
			 HitInfo& _hitInfo, const vector<Shape*>& _ignoredShapes, const float _precision = 0.01f);

vector<HitInfo> RaycastAll(const Vector2f& _origin, const Vector2f& _direction, const float _maxDistance,
						   const vector<Shape*>& _ignoredShapes, const float _precision = 0.01f);
 
vector<Actor*> Boxcast(Shape* _shape, const vector<Actor*>& _actors);