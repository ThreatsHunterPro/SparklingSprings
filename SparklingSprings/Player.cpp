#include "Player.h"

// Managers
#include "ActorManager.h"
#include "InputManager.h"
#include "Action.h"
#include "Timer.h"
#include "Resource.h"

// UI
#include "Canvas.h"
#include "ProgressBar.h"

#include "Kismet.h"

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
	craftBook = nullptr;
	skillTree = nullptr;

	overworldInputs = nullptr;
	donjonInputs = nullptr;

	movement = new PlayerMovementComponent(this);
	components.push_back(movement);

	interact = new InteractComponent(this);
	components.push_back(interact);
	
	gather = new GatherComponent(this);
	components.push_back(gather);
}


void Player::SetupPlayerInput()
{
	/*new ActionMap("PlayerStats", {
		ActionData("TakeDamages", [&]()
		{
			stats->TakeDamages(-30.0f);
			stats->StopHealthRegen();
		}, { ActionType::MouseButtonPressed, Mouse::Left }),
		ActionData("UseMana", [&]() { stats->UseMana(-50.0f); }, { ActionType::MouseButtonPressed, Mouse::Right }),
		ActionData("Drink", [&]() { stats->Drink(40.0f); }, { ActionType::KeyPressed, Keyboard::A }),
		ActionData("Eat", [&]() { stats->Eat(30.0f); }, { ActionType::KeyPressed, Keyboard::E }),
		});*/
	overworldInputs = new ActionMap("Overworld", {

		#pragma region Movement

		ActionData("Overworld_Forward", [&]() { movement->SetDirectionY(-1.0f); }, InputData({ ActionType::KeyPressed, Keyboard::Z })),
		ActionData("Overworld_StopForward", [&]() { movement->SetDirectionY(0.0f); }, InputData({ ActionType::KeyReleased, Keyboard::Z })),

		ActionData("Overworld_Backward", [&]() { movement->SetDirectionY(1.0f); }, InputData({ ActionType::KeyPressed, Keyboard::S })),
		ActionData("Overworld_StopBackward", [&]() { movement->SetDirectionY(0.0f); }, InputData({ ActionType::KeyReleased, Keyboard::S })),

		ActionData("Overworld_Left", [&]() { movement->SetDirectionX(-1.0f); }, InputData({ ActionType::KeyPressed, Keyboard::Q })),
		ActionData("Overworld_StopLeft", [&]() { movement->SetDirectionX(0.0f); }, InputData({ ActionType::KeyReleased, Keyboard::Q })),

		ActionData("Overworld_Right", [&]() { movement->SetDirectionX(1.0f); }, InputData({ ActionType::KeyPressed, Keyboard::D })),
		ActionData("Overworld_StopRight", [&]() { movement->SetDirectionX(0.0f); }, InputData({ ActionType::KeyReleased, Keyboard::D })),

		ActionData("Sprint", [&]() { movement->SetSprint(true); }, InputData({ ActionType::KeyPressed, Keyboard::LControl })),
		ActionData("StopSprint", [&]() { movement->SetSprint(false); }, InputData({ ActionType::KeyReleased, Keyboard::LControl })),

		#pragma endregion

		#pragma region Interaction

		ActionData("Interact", [&]() { interact->Interact(); }, InputData({ ActionType::MouseButtonPressed, Mouse::Left })),

		#pragma endregion
	});
	donjonInputs = new ActionMap("Donjon", {

		#pragma region Movement

		ActionData("Overworld_Left", [&]() { movement->SetDirectionX(-1.0f); }, InputData({ ActionType::KeyPressed, Keyboard::Q })),
		ActionData("Overworld_StopLeft", [&]() { movement->SetDirectionX(0.0f); }, InputData({ ActionType::KeyReleased, Keyboard::Q })),

		ActionData("Overworld_Right", [&]() { movement->SetDirectionX(1.0f); }, InputData({ ActionType::KeyPressed, Keyboard::D })),
		ActionData("Overworld_StopRight", [&]() { movement->SetDirectionX(0.0f); }, InputData({ ActionType::KeyReleased, Keyboard::D })),

		ActionData("Jump", [&]() { movement->Jump(); }, InputData({ ActionType::KeyPressed, Keyboard::Space })),
		ActionData("Dash", [&]() { movement->Dash(); }, InputData({ ActionType::KeyPressed, Keyboard::LControl })),

		#pragma endregion

		#pragma region Fight

		ActionData("LightAttack", [&]() { LightAttack(); }, InputData({ ActionType::MouseButtonPressed, Mouse::Left })),
		ActionData("HeavyAttack", [&]() { HeavyAttack(); }, InputData({ ActionType::MouseButtonPressed, Mouse::Right })),

		#pragma endregion
	}, false);
	new ActionMap("Storages", {
		ActionData("Inventory", [&]() { inventory->Toggle(); }, InputData({ ActionType::KeyPressed, Keyboard::B })),
	});

	//TODO remove
	new ActionMap("TEMP", {
		ActionData("SwapActionMap", [&]() { SwapActionMap(); }, InputData({ ActionType::KeyPressed, Keyboard::P })),
	});

	//TODO remove
	new InteractableActor(InteractableData("Floor", ShapeData(Vector2f(50.0f, 650.0f), Vector2f(1100.0f, 50.0f), ""), []() {
			cout << "C'est le sol ca connard !" << endl;
		})
	);

	static Resource* _tree = new Resource(
		InteractableData("Tree", ShapeData(Vector2f(400.0f, 200.0f), Vector2f(50.0f, 50.0f), ""), [&]() {
			cout << "Gather tree !" << endl;
			gather->Gather(_tree);
		}),
		ResourceData(PATH_WOOD, ITEM_RESOURCE, RARITY_COMMON, 3, 5.0f, 0.1f)
	);
	static Resource* _rock = new Resource(
		InteractableData("Rock", ShapeData(Vector2f(600.0f, 200.0f), Vector2f(50.0f, 50.0f), ""), [&]() {
			gather->Gather(_rock);
		}),
		ResourceData(PATH_ROCK, ITEM_RESOURCE, RARITY_COMMON, 1, 2.0f, 0.1f)
	);
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

	/*ProgressBar* _healthBar = new ProgressBar(ShapeData(Vector2f(_posX, _posY), Vector2f(_sizeX, _sizeY), PATH_HEALTH_BAR_EMPTY),
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

	stats = new PlayerStats(_healthBar, _manaBar, _thirstBar, _hungerBar);*/

	ProgressBar* _gatherBar = new ProgressBar(ShapeData(Vector2f(50.0f, 50.0f), Vector2f(_sizeX, _sizeY), PATH_HUNGER_BAR_EMPTY),
											  _canvas, PATH_HUNGER_BAR_FULL, ProgressType::PT_LEFT, 100.0f);
	_canvas->AddWidget(_gatherBar);
	gather->SetProgressBar(_gatherBar);
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

void Player::SwapActionMap()
{
	overworldInputs->isActive = !overworldInputs->isActive;
	donjonInputs->isActive = !donjonInputs->isActive;
	movement->SetCanJumpAndDash(donjonInputs->isActive);
}


void Player::Init()
{
	SetupPlayerInput();
	InitHUD();
}