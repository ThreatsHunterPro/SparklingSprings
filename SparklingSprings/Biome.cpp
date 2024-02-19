#include "Biome.h"
#include "Macro.h"
#include "BiomeManager.h"
#include <cmath>

Biome::Biome(const TileType& _type, const Vector2f& _position, const Vector2i& _size, const Vector2i& _biomeSize, const int _securityZone) : IManagable(STRING_ID("Biome"))
{
	biome = vector<vector<Tile*>>();
	const Vector2f& _tileSize = Vector2f(float(_size.x), float(_size.y));
	securityZoneSize = _securityZone;
	InitBiome(_type, _position, _tileSize,_biomeSize);
}

void Biome::InitBiome(const TileType& _type, const Vector2f& _position, const Vector2f& _size, const Vector2i& _biomeSize)
{
	const Vector2i& _tilesCount = _biomeSize;
	for (int _y = 0; _y < _tilesCount.y; _y++)
	{
		vector<Tile*> _row;
		for (int _x = 0; _x < _tilesCount.x; _x++)
		{
			const Vector2i& _middle = _biomeSize / 2;
			const int _minMiddleX = _middle.x - securityZoneSize / 2;
			const int _maxMiddleY = _middle.y + securityZoneSize / 2;
			const int _minMiddleY = _middle.y - securityZoneSize / 2;
			const int _maxMiddleX = _middle.x + securityZoneSize / 2;

			/*const int _currentMiddleX = _x <= _middle.x ? _minMiddleX : _maxMiddleX;
			const int _currentMiddleY = _y <= _middle.y ? _minMiddleY : _maxMiddleY;
			const int _distanceX = abs(_currentMiddleX - _x);
			const int _distanceY = abs(_currentMiddleY - _y);*/

			const int _distanceX = abs(_middle.x - _x);
			const int _distanceY = abs(_middle.y - _y);
			const int _distance = (_distanceX + _distanceY) / 2;
			const int _distancePow = (int)exp(_distance); //pow(2, _distance + int(_distance * 0.5f));
			//const int _distancePow = pow(2, _distance + int(_distance * 0.5f));

			int _chance = 150 - _distancePow * (_distance - (securityZoneSize / 2));
			if (_chance <= 20)
			{
				_chance = 20 - 5 * (_distance - (securityZoneSize / 2));
			}
			const bool _isOnSecurityZone = _x <= _maxMiddleX && _x >= _minMiddleX && _y <= _maxMiddleY && _y >= _minMiddleY;
			const TileType& _realType = (_chance > 0 && Random(_chance + 1) != 0) || _isOnSecurityZone || _chance >= 100 ? _type : TT_NONE;
			const Vector2f& _tilePos = _position + Vector2f(_position.x * 5.0f, _position.y) + Vector2f(_x * _size.x, _y * _size.y);
			Tile* _tile = BiomeManager::GetInstance().GetTileByPosition(_tilePos);
			cout << _realType << endl;
			if (_realType != TT_NONE)
			{
				_tile->SetType(_realType);
			}
		}
	}
}

void Biome::Register()
{
	BiomeManager::GetInstance().Add(id, this);
}
