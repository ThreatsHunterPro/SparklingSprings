#include "Player.h"
#include "Action.h"
#include "InputManager.h"
#include "Canvas.h"
#include "Button.h"
#include "ProgressBar.h"
#include "Timer.h"

#pragma region Defines

#pragma region ProgressBar

#define PATH_HEALTH_BAR_EMPTY "UIs/Bars/Health/Empty.png"
#define PATH_HEALTH_BAR_FULL "UIs/Bars/Health/Full.png"

#define PATH_MANA_BAR_EMPTY "UIs/Bars/Mana/Empty.png"
#define PATH_MANA_BAR_FULL "UIs/Bars/Mana/Full.png"

#define PATH_THIRST_BAR_EMPTY "UIs/Bars/Thirst/Empty.png"
#define PATH_THIRST_BAR_FULL "UIs/Bars/Thirst/Full.png"

#define PATH_HUNGER_BAR_EMPTY "UIs/Bars/Hunger/Empty.png"
#define PATH_HUNGER_BAR_FULL "UIs/Bars/Hunger/Full.png"

#pragma endregion

#pragma endregion

Player::Player(const string& _name, const ObjectData& _data) : Actor(_name,_data)
{
	stats = nullptr;
}


void Player::SetupPlayerInput()
{
	new ActionMap("PlayerStats", {
		ActionData("TakeDamages", [&]()
		{
			stats->TakeDamages(-30.0f);
			stats->StopHealthRegen();

		}, { ActionType::MouseButtonPressed, Mouse::Left }),
		ActionData("UseMana", [&]()
		{
			stats->UseMana(-50.0f);

		}, { ActionType::MouseButtonPressed, Mouse::Right }),
		ActionData("Drink", [&]()
		{
			stats->Drink(40.0f);

		}, { ActionType::KeyPressed, Keyboard::D }),
			ActionData("Eat", [&]()
		{
			stats->Eat(30.0f);

		}, { ActionType::KeyPressed, Keyboard::E }),
	});
}

void Player::InitHUD()
{
	Canvas* _canvas = new Canvas("PlayerHUD", FloatRect(0, 0, 1, 1));

	float _sizeX = 200.0f; float _sizeY = 150.0f;
	float _posX = 10.0f; float _posY = 10.0f;

	ProgressBar* _healthBar = new ProgressBar(ObjectData(Vector2f(_posX, _posY), Vector2f(_sizeX, _sizeY), PATH_HEALTH_BAR_EMPTY),
							  _canvas, PATH_HEALTH_BAR_FULL, ProgressType::PT_LEFT, 1000.0f);
	_canvas->AddWidget(_healthBar);

	ProgressBar* _manaBar = new ProgressBar(ObjectData(Vector2f(_posX, _posY + 50.0f), Vector2f(_sizeX, _sizeY), PATH_MANA_BAR_EMPTY),
							_canvas, PATH_MANA_BAR_FULL, ProgressType::PT_LEFT, 1000.0f);
	_canvas->AddWidget(_manaBar);

	ProgressBar* _thirstBar = new ProgressBar(ObjectData(Vector2f(_posX, _posY + 100.0f), Vector2f(_sizeX, _sizeY), PATH_THIRST_BAR_EMPTY),
							  _canvas, PATH_THIRST_BAR_FULL, ProgressType::PT_LEFT, 1000.0f);
	_canvas->AddWidget(_thirstBar);

	ProgressBar* _hungerBar = new ProgressBar(ObjectData(Vector2f(_posX, _posY + 150.0f), Vector2f(_sizeX, _sizeY), PATH_HUNGER_BAR_EMPTY),
							  _canvas, PATH_HUNGER_BAR_FULL, ProgressType::PT_LEFT, 1000.0f);
	_canvas->AddWidget(_hungerBar);

	stats = new PlayerStats(_healthBar, _manaBar, _thirstBar, _hungerBar);
}

void Player::Init()
{
	SetupPlayerInput();
	InitHUD();
}