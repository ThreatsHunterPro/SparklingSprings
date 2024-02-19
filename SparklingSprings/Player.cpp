#include "Player.h"
#include "Action.h"
#include "InputManager.h"
#include "Canvas.h"
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

#define PATH_WOOD "Wood.png"
#define PATH_ROCK "Rock.png"

#pragma endregion

Player::Player(const string& _name, const ShapeData& _data) : Actor(_name,_data)
{
	stats = nullptr;
	inventory = new Inventory();
	movement = new PlayerMovementComponent(this);
	components.push_back(movement);
}


void Player::SetupPlayerInput()
{
	new ActionMap("PlayerStats", {
		ActionData("TakeDamages", [&]()
		{
			stats->TakeDamages(-30.0f);
			stats->StopHealthRegen();
		}, { ActionType::MouseButtonPressed, Mouse::Left }),
		ActionData("UseMana", [&]() { stats->UseMana(-50.0f); }, { ActionType::MouseButtonPressed, Mouse::Right }),
		ActionData("Drink", [&]() { stats->Drink(40.0f); }, { ActionType::KeyPressed, Keyboard::A }),
		ActionData("Eat", [&]() { stats->Eat(30.0f); }, { ActionType::KeyPressed, Keyboard::E }),
		});
	new ActionMap("Movement", {
		ActionData("P_Forward", [&]() { movement->SetDirectionY(-1.0f); }, InputData({ ActionType::KeyPressed, Keyboard::Z })),
		ActionData("R_Forward", [&]() { movement->SetDirectionY(0.0f); }, InputData({ ActionType::KeyReleased, Keyboard::Z })),

		ActionData("P_Backward", [&]() { movement->SetDirectionY(1.0f); }, InputData({ ActionType::KeyPressed, Keyboard::S })),
		ActionData("R_Backward", [&]() { movement->SetDirectionY(0.0f); }, InputData({ ActionType::KeyReleased, Keyboard::S })),

		ActionData("P_Left", [&]() { movement->SetDirectionX(-1.0f); }, InputData({ ActionType::KeyPressed, Keyboard::Q })),
		ActionData("R_Left", [&]() { movement->SetDirectionX(0.0f); }, InputData({ ActionType::KeyReleased, Keyboard::Q })),

		ActionData("P_Right", [&]() { movement->SetDirectionX(1.0f); }, InputData({ ActionType::KeyPressed, Keyboard::D })),
		ActionData("R_Right", [&]() { movement->SetDirectionX(0.0f); }, InputData({ ActionType::KeyReleased, Keyboard::D })),
		});
	new ActionMap("Fight", {
		ActionData("LightAttack", [&]() { LightAttack(); }, InputData({ ActionType::MouseButtonPressed, Keyboard::Left })),
		ActionData("HeavyAttack", [&]() { HeavyAttack(); }, InputData({ ActionType::MouseButtonPressed, Keyboard::Right })),
	});
	new ActionMap("Storages", {
		ActionData("Inventory", [&]() { inventory->Toggle(); }, InputData({ ActionType::KeyPressed, Keyboard::B })),
		ActionData("AddItem1", [&]() { inventory->AddItem(PATH_WOOD, ITEM_RESOURCE, RARITY_COMMON); }, InputData({ ActionType::KeyPressed, Keyboard::X })),
		ActionData("AddItem2", [&]() { inventory->AddItem(PATH_ROCK, ITEM_RESOURCE, RARITY_COMMON); }, InputData({ ActionType::KeyPressed, Keyboard::C })),
	});
}

void Player::InitHUD()
{
	InitStats();
	InitSkillTree();
}

void Player::InitStats()
{
	Canvas* _canvas = new Canvas("PlayerStats", FloatRect(0, 0, 1, 1));

	float _sizeX = 200.0f; float _sizeY = 150.0f;
	float _posX = 10.0f; float _posY = 10.0f;

	ProgressBar* _healthBar = new ProgressBar(ShapeData(Vector2f(_posX, _posY), Vector2f(_sizeX, _sizeY), PATH_HEALTH_BAR_EMPTY),
		_canvas, PATH_HEALTH_BAR_FULL, ProgressType::PT_LEFT, 1000.0f);
	_canvas->AddWidget(_healthBar);

	ProgressBar* _manaBar = new ProgressBar(ShapeData(Vector2f(_posX, _posY + 50.0f), Vector2f(_sizeX, _sizeY), PATH_MANA_BAR_EMPTY),
		_canvas, PATH_MANA_BAR_FULL, ProgressType::PT_LEFT, 1000.0f);
	_canvas->AddWidget(_manaBar);

	ProgressBar* _thirstBar = new ProgressBar(ShapeData(Vector2f(_posX, _posY + 100.0f), Vector2f(_sizeX, _sizeY), PATH_THIRST_BAR_EMPTY),
		_canvas, PATH_THIRST_BAR_FULL, ProgressType::PT_LEFT, 1000.0f);
	_canvas->AddWidget(_thirstBar);

	ProgressBar* _hungerBar = new ProgressBar(ShapeData(Vector2f(_posX, _posY + 150.0f), Vector2f(_sizeX, _sizeY), PATH_HUNGER_BAR_EMPTY),
		_canvas, PATH_HUNGER_BAR_FULL, ProgressType::PT_LEFT, 1000.0f);
	_canvas->AddWidget(_hungerBar);

	stats = new PlayerStats(_healthBar, _manaBar, _thirstBar, _hungerBar);
}

void Player::InitSkillTree()
{
	Canvas* _canvas = new Canvas("SkillTree", FloatRect(0, 0, 1, 1));
}

//TODO move
void Player::LightAttack()
{
	cout << "LightAttack" << endl;
}

void Player::HeavyAttack()
{
	cout << "HeavyAttack" << endl;
}


void Player::Init()
{
	SetupPlayerInput();
	InitHUD();
}