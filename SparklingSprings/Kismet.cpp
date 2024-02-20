#include "Kismet.h"
#include "Macro.h"
#include "ActorManager.h"

bool Raycast(const Vector2f& _origin, const Vector2f& _direction, const float _maxDistance,
			 HitInfo& _hitInfo, const vector<Shape*>& _ignoredShapes, const float _precision)
{
	if (_direction == Vector2f()) return false;

	Vector2f _currentPosition = _origin;
	float _distance = 0.0f;

	while (Distance(_origin, _currentPosition) < _maxDistance)
	{
		for (Actor* _actor : ActorManager::GetInstance().GetAllValues())
		{
			Shape* _shape = _actor->GetDrawable();
			if (Contains(_shape, _ignoredShapes)) continue;

			if (_shape->getGlobalBounds().contains(_currentPosition))
			{
				_hitInfo.position = _currentPosition;
				_hitInfo.distance = _distance;
				_hitInfo.actor = _actor;

				return true;
			}
		}

		_distance += _precision;
		_currentPosition += _direction * _distance;
	}

	return false;
}

vector<HitInfo> RaycastAll(const Vector2f& _origin, const Vector2f& _direction, const float _maxDistance,
						   const vector<Shape*>& _ignoredShapes, const float _precision)
{
	vector<HitInfo> _hitInfos;
	if (_direction == Vector2f()) return _hitInfos;

	Vector2f _currentPosition = _origin;
	float _distance = 0.0f;

	while (Distance(_origin, _currentPosition) < _maxDistance)
	{
		for (Actor* _actor : ActorManager::GetInstance().GetAllValues())
		{
			Shape* _shape = _actor->GetDrawable();
			if (Contains(_shape, _ignoredShapes)) continue;

			if (_shape->getGlobalBounds().contains(_currentPosition))
			{
				HitInfo _hitInfo;
				_hitInfo.position = _currentPosition;
				_hitInfo.distance = _distance;
				_hitInfo.actor = _actor;

				_hitInfos.push_back(_hitInfo);
			}
		}

		_distance += _precision;
		_currentPosition += _direction * _distance;
	}

	return _hitInfos;
}