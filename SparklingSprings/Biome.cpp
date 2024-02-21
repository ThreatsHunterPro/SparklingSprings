#include "Biome.h"
#include "BiomeManager.h"
#include "Macro.h"

Biome::Biome(const TileType& _type, const Vector2i& _size, const Vector2i& _securityZone) : IManagable(STRING_ID("Biome"))
{
	type = _type;
	size = _size;
	securityZoneSize = _securityZone;
	tiles = vector<vector<Tile*>>();
}


void Biome::Register()
{
	BiomeManager::GetInstance().Add(id, this);
}

void Biome::Init(const Vector2f& _position, const Vector2f& _tileSize)
{
	int _triesCount = 0;

	for (int _rowIndex = 0; _rowIndex < size.y; _rowIndex++)
	{
		vector<Tile*> _row;

		for (int _columnIndex = 0; _columnIndex < size.x; _columnIndex++)
		{
			// Calcul par la case à 100% la plus proche
			const float _targetX = _position.x + _columnIndex * _tileSize.x;
			const float _targetY = _position.y + _rowIndex * _tileSize.y;
			Vector2f _closestTile = FindClosestSecurityTile(Vector2i(_columnIndex, _rowIndex), Vector2f(_targetX, _targetY));
			
			const float _distanceX = abs(_closestTile.x - _columnIndex);
			const float _distanceY = abs(_closestTile.y - _rowIndex);
			const int _distance = int((_distanceX + _distanceY) / 2.0f);
			const int _distancePow = (int)exp(_distance);

			const int _securityZoneAverage = (securityZoneSize.x + securityZoneSize.y) / 2;
			int _chance = 80 - _distancePow * (_distance - _securityZoneAverage / 2);
			if (_chance <= 20)
			{
				_chance = 20 - 5 * (_distance - (_securityZoneAverage / 2));
			}

			const Vector2f& _tilePosition = _position + Vector2f(_columnIndex * _tileSize.x, _rowIndex * _tileSize.y);
			const TileType& _realType = IsInSecurityZone(_columnIndex, _rowIndex) || _chance >= 100
									 || (_chance > 0 && Random(_chance + 1) != 0) ? type : TT_NONE;

			Tile* _tile = BiomeManager::GetInstance().GetTileByPosition(_tilePosition);
			if (!_tile)
			{
				cout << "Not found :" << _triesCount << endl;
				_triesCount++;

				if (_triesCount < 10)
				{
					_columnIndex--;
				}

				continue;
			}

			_triesCount = 0;
			_tile->SetColorWithType(_realType);

			#pragma region ChanceColor

			Color _color;
			if (IsInSecurityZone(_columnIndex, _rowIndex) || _chance > 100)
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

			#pragma endregion

			_row.push_back(_tile);
		}

		tiles.push_back(_row);
	}
}