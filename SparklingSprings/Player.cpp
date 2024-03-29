#include "Player.h"

// Managers
#include "ActorManager.h"
#include "InputManager.h"
#include "Action.h"
#include "Timer.h"
#include "Resource.h"
#include "Transporter.h"

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

Player::Player(const string& _name, const ShapeData& _data) : Actor(_name, _data)
{
	InitStats();

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
	
	fight = new FightComponent(this);
	components.push_back(fight);

	Init();
}


void Player::Init()
{
	SetupPlayerInput();
	InitHUD();
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

		ActionData("LightAttack", [&]() { fight->LightAttack(); }, InputData({ ActionType::MouseButtonPressed, Mouse::Left })),
		ActionData("HeavyAttack", [&]() { fight->HeavyAttack(); }, InputData({ ActionType::MouseButtonPressed, Mouse::Right })),

		#pragma endregion
	}, false);
	new ActionMap("Storages", {
		ActionData("Inventory", [&]() { inventory->Toggle(); }, InputData({ ActionType::KeyPressed, Keyboard::B })),
	});

	//TODO remove
	new ActionMap("TEMP", {
		ActionData("SwapActionMap", [&]() { SwapActionMap(); }, InputData({ ActionType::KeyPressed, Keyboard::P })),
		ActionData("HideHUD", [&]() { canvas->SetVisibilityStatus(!canvas->IsVisible()); }, InputData({ ActionType::KeyPressed, Keyboard::M })),
	});
	//TODO remove
	new InteractableActor(InteractableData("Floor", ShapeData(Vector2f(50.0f, 650.0f), Vector2f(1100.0f, 50.0f), ""), []() {
			cout << "C'est le sol ca connard !" << endl;
		})
	);
	//TODO remove
	static Resource* _tree = new Resource(
		InteractableData("Tree", ShapeData(Vector2f(400.0f, 200.0f), Vector2f(50.0f, 50.0f), ""), [&]() {
			gather->Gather(_tree);
		}),
		ResourceData(PATH_WOOD, ITEM_RESOURCE, RARITY_COMMON, 3, 5.0f, 0.01f)
	);
	//TODO remove
	static Resource* _rock = new Resource(
		InteractableData("Rock", ShapeData(Vector2f(600.0f, 200.0f), Vector2f(50.0f, 50.0f), ""), [&]() {
			gather->Gather(_rock);
		}),
		ResourceData(PATH_ROCK, ITEM_RESOURCE, RARITY_COMMON, 1, 2.0f, 0.01f)
	);
	//TODO remove
	new Enemy("Enemy", ShapeData(Vector2f(800.0f, 550.0f), Vector2f(100.0f, 100.0f), ""));
	//TODO remove
	static Transporter* _transporter = new Transporter(InteractableData("Transporter" + to_string(GetUniqueID()),
													   ShapeData(Vector2f(500.0f, 300.0f), Vector2f(30.0f, 30.0f), ""),
													   [&]() { _transporter->Teleport(this); }),
													   Vector2f(800.0f, 200.0f));
}

void Player::InitHUD()
{
	ProgressBar* _gatherBar = new ProgressBar(ShapeData(Vector2f(50.0f, 50.0f), Vector2f(200.0f, 150.0f), PATH_HUNGER_BAR_EMPTY),
											  canvas, PATH_HUNGER_BAR_FULL, ProgressType::PT_LEFT, 100.0f);
	canvas->AddWidget(_gatherBar);
	gather->SetProgressBar(_gatherBar);

	InitSkillTree();
}

void Player::InitStats()
{
	canvas = new Canvas("PlayerStats", FloatRect(0, 0, 1, 1));

	float _sizeX = 200.0f; float _sizeY = 150.0f;
	float _posX = 10.0f; float _posY = 10.0f;

	ProgressBar* _healthBar = new ProgressBar(ShapeData(Vector2f(_posX, _posY), Vector2f(_sizeX, _sizeY), PATH_HEALTH_BAR_EMPTY),
											  canvas, PATH_HEALTH_BAR_FULL, ProgressType::PT_LEFT, 1000.0f);
	canvas->AddWidget(_healthBar);

	ProgressBar* _manaBar = new ProgressBar(ShapeData(Vector2f(_posX, _posY + 50.0f), Vector2f(_sizeX, _sizeY), PATH_MANA_BAR_EMPTY),
											  canvas, PATH_MANA_BAR_FULL, ProgressType::PT_LEFT, 1000.0f);
	canvas->AddWidget(_manaBar);

	ProgressBar* _thirstBar = new ProgressBar(ShapeData(Vector2f(_posX, _posY + 100.0f), Vector2f(_sizeX, _sizeY), PATH_THIRST_BAR_EMPTY),
											  canvas, PATH_THIRST_BAR_FULL, ProgressType::PT_LEFT, 1000.0f);
	canvas->AddWidget(_thirstBar);

	ProgressBar* _hungerBar = new ProgressBar(ShapeData(Vector2f(_posX, _posY + 150.0f), Vector2f(_sizeX, _sizeY), PATH_HUNGER_BAR_EMPTY),
											  canvas, PATH_HUNGER_BAR_FULL, ProgressType::PT_LEFT, 1000.0f);
	canvas->AddWidget(_hungerBar);

	stats = new PlayerStats(_healthBar, _manaBar, _thirstBar, _hungerBar);
}

void Player::InitSkillTree()
{
	Canvas* _canvas = new Canvas("SkillTree", FloatRect(0, 0, 1, 1));
}

void Player::SwapActionMap()
{
	overworldInputs->isActive = !overworldInputs->isActive;
	donjonInputs->isActive = !donjonInputs->isActive;
	movement->SetCanJumpAndDash(donjonInputs->isActive);
}