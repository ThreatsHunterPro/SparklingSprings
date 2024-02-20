#include "Kismet.h"
#include "Macro.h"
#include "ActorManager.h"

bool Raycast(const Vector2f& _origin, const Vector2f& _direction, const float _maxDistance,
			 HitInfo& _hitInfo, const vector<Shape*>& _ignoredShapes, const float _precision)
{
	Vector2f _currentPosition = _origin;
	float _distance = 0.0f;

	while (_distance < _maxDistance)
	{
		for (Actor* _actor : ActorManager::GetInstance().GetAllValues())
		{
			Shape* _shape = _actor->GetDrawable();
			if (Contains(_shape, _ignoredShapes)) continue;

			if (_shape->getGlobalBounds().contains(_currentPosition))
			{
				_hitInfo.position = _currentPosition;
				_hitInfo.distance = _distance;

				return true;
			}
		}

		_distance += _precision;
		_currentPosition += _direction * _distance;
	}

	return false;
}

vector<HitInfo> RaycastAll(const Vector2f& _origin, const Vector2f& _direction,
						   const float _maxDistance, const float _precision)
{
	vector<HitInfo> _hitInfos;

	Vector2f _currentPosition = _origin;
	float _distance = 0.0f;

	while (_distance < _maxDistance)
	{
		for (Actor* _actor : ActorManager::GetInstance().GetAllValues())
		{
			if (_actor->GetDrawable()->getGlobalBounds().contains(_currentPosition))
			{
				HitInfo _hitInfo;
				_hitInfo.position = _currentPosition;
				_hitInfo.distance = _distance;

				_hitInfos.push_back(_hitInfo);
			}
		}

		_distance += _precision;
		_currentPosition += _direction * _distance;
	}

	return _hitInfos;
}