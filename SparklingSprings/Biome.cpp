#include "Biome.h"
#include "Macro.h"
#include "BiomeManager.h"

Biome::Biome(const TileType& _type, const Vector2f& _position, const Vector2i& _size, const Vector2i& _biomeSize, const int _securityZone) : IManagable(STRING_ID("Biome"))
{
	biome = vector<vector<Tile*>>();
	const Vector2f& _tileSize = Vector2f(float(_size.x), float(_size.y));
	InitBiome(_type, _position, _tileSize, _biomeSize);
	securityZoneSize = _securityZone;
}

void Biome::InitBiome(const TileType& _type, const Vector2f& _position, const Vector2f& _size, const Vector2i& _biomeSize)
{
	const Vector2i& _tilesCount = _biomeSize;

	for (int _y = 0; _y < _tilesCount.y; _y++)
	{
		vector<Tile*> _row;
		for (int _x = 0; _x < _tilesCount.x; _x++)
		{
			const int _average = int((_biomeSize.x + _biomeSize.y) / 2.0f);
			const int _factor = 100 / _average;

			const Vector2i& _middle = _biomeSize / 2;
			const int _distanceX = abs(_middle.x - _x);
			const int _distanceY = abs(_middle.y - _y);
			const int _distance = (_distanceX + _distanceY) / 2;

			const int _chance = 100 - _factor * _distance;
			const TileType& _realType = Random(_chance + 1) != 0 ? _type : TT_NONE;
			const Vector2f& _tilePos = _position + Vector2f(_x * _size.x, _y * _size.y);
			Tile* _tile = new Tile("Tile" + to_string(GetUniqueID()), _realType, _tilePos, _size);

			Color _color;
			if (_chance >= 100)
			{
				_color = Color::Red;
			}
			else if (_chance >= 80)
			{
				_color = Color::Magenta;
			}
			else if (_chance >= 60)
			{
				_color = Color::Blue;
			}
			else if (_chance >= 40)
			{
				_color = Color::Cyan;
			}
			else if (_chance >= 20)
			{
				_color = Color::Yellow;
			}
			else if (_chance >= 0)
			{
				_color = Color::Green;
			}
			else
			{
				_color = Color::White;
			}
			_tile->GetDrawable()->setFillColor(_color);

			_row.push_back(_tile);
		}

		biome.push_back(_row);
	}
}

void Biome::Register()
{
	BiomeManager::GetInstance().Add(id, this);
}
