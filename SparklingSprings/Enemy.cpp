#include "Enemy.h"

#define PATH_HEALTH_BAR_EMPTY "UIs/Bars/Health/Empty.png"
#define PATH_HEALTH_BAR_FULL "UIs/Bars/Health/Full.png"

Enemy::Enemy(const string& _name, const ShapeData& _data) : Actor(_name, _data)
{
	InitHUD();
}


void Enemy::InitHUD()
{
	Canvas* _canvas = new Canvas("Enemy" + to_string(GetUniqueID()), FloatRect(0, 0, 1, 1));
	float _sizeX = 200.0f; float _sizeY = 150.0f;
	ProgressBar* _healthBar = new ProgressBar(ShapeData(Vector2f(50.0f, 50.0f), Vector2f(_sizeX, _sizeY), PATH_HEALTH_BAR_EMPTY),
											  _canvas, PATH_HEALTH_BAR_FULL, ProgressType::PT_LEFT, 100.0f);
	_canvas->AddWidget(_healthBar);
	health = new Stat(1.0f, _healthBar);
}

void Enemy::SetDamages(const float _damages)
{
	health->Update(-_damages);
}