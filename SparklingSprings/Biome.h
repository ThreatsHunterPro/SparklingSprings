#pragma once
#include "Tile.h"
#include "IManagable.h"

class Biome : public IManagable<string>
{
	TileType type;
	Vector2i size;
	Vector2i securityZoneSize;
	vector<vector<Tile*>> tiles;

public:
	Biome(const TileType& _type, const Vector2i& _size, const Vector2i& _securityZone);

private:
	virtual void Register() override;
	bool IsInSecurityZone(const int _columnIndex, const int _rowIndex)
	{
		const Vector2i& _halfSize = size / 2;
		const int _minMiddleX = _halfSize.x - securityZoneSize.x / 2;
		const int _maxMiddleX = _halfSize.x + securityZoneSize.x / 2;
		const int _minMiddleY = _halfSize.y - securityZoneSize.y / 2;
		const int _maxMiddleY = _halfSize.y + securityZoneSize.y / 2;

		return _columnIndex <= _maxMiddleX && _columnIndex >= _minMiddleX
			&& _rowIndex <= _maxMiddleY && _rowIndex >= _minMiddleY;
	}
	Vector2f FindClosestSecurityTile(const Vector2i& _position, const Vector2f& _tileSize)
	{
		Vector2f _closestPos;

		// Direction entre la current et le centre
		const Vector2i& _center = size / 2;
		const Vector2i& _direction = _center - _position;
		const bool _isOverX = _position.x > _center.x;
		const bool _isOverY = _position.y > _center.y;

		// On Ajoute/retirer au centre securityZone / 2 * tileSize
		const int _closestPosX = _isOverX ? securityZoneSize.x / 2 : -securityZoneSize.x / 2;
		const int _closestPosY = _isOverY ? securityZoneSize.y / 2 : -securityZoneSize.y / 2;
		_closestPos = Vector2f(_center.x + float(_closestPosX), _center.y + float(_closestPosY));

		// & 0 0 0 0 0 0 0 0 0
		// 0 0 0 0 0 0 0 0 0 0
		// 0 0 0 0 0 0 0 0 0 0
		// 0 0 0 0 0 0 0 0 0 0
		// 0 0 0 0 # # # 0 0 0
		// 0 0 0 0 # # # 0 0 0
		// 0 0 0 0 # # # 0 0 0
		// 0 0 0 0 0 0 0 0 0 0
		// 0 0 0 0 0 0 0 0 0 0
		// 0 0 0 0 0 0 0 0 0 0

		//#pragma region Clamps

		// Par contre ca doit pas passer en dessous de la pos initiale
		if (_isOverX)
		{
			_closestPos.x = _closestPos.x > _position.x ? _position.x : _closestPos.x;
		}
		else
		{
			_closestPos.x = _closestPos.x < _position.x ? _position.x : _closestPos.x;
		}
		
		if (_isOverY)
		{
			_closestPos.y = _closestPos.y > _position.y ? _position.y : _closestPos.y;
		}
		else
		{
			_closestPos.y = _closestPos.y < _position.y ? _position.y : _closestPos.y;
		}

		//#pragma endregion

		return _closestPos;
	}

public:
	void Init(const Vector2f& _position, const Vector2f& _tileSize);
};