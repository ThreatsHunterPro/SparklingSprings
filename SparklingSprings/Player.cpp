#include "Player.h"
#include "Action.h"
#include "InputManager.h"
#include "Canvas.h"
#include "Button.h"
#include "ProgressBar.h"
#include "Timer.h"

#pragma region Defines

#define PATH_UNIT_ICON "UIs/UnitIcon.png"
#define PATH_SPELL_ICON "UIs/Spells/Icon.png"
#define PATH_SPELL_HAMMER_STRIKE "UIs/Spells/HammerStrike.png"
#define PATH_BUTTONS "UIs/Buttons.png"

#pragma region ProgressBar

// Coins
#define PATH_COINS_BAR_EMPTY "UIs/Bars/Coins/Empty.png"
#define PATH_COINS_BAR_FULL "UIs/Bars/Coins/Full.png"

// Units
#define PATH_UNITS_BAR_EMPTY "UIs/Bars/Units/Empty.png"
#define PATH_UNITS_BAR_FULL "UIs/Bars/Units/Full.png"

// Castle
#define PATH_CASTLE_BAR_EMPTY "UIs/Bars/Castle/Empty.png"
#define PATH_CASTLE_BAR_FULL "UIs/Bars/Castle/Full.png"

#pragma endregion

#pragma endregion

Player::Player(const string& _name, const ObjectData& _data) : Character(_name, _data)
{
	SetupPlayerInput();
	InitHUD();
}


void Player::SetupPlayerInput()
{
	new Action(ActionData("MovePlayer", [&]() {
		const Vector2f& _mousePosition = InputManager::GetInstance().GetMousePosition(); 
		movement->SetDestination(_mousePosition);
	}, { ActionType::MouseButtonPressed, Mouse::Left }), "PlayerInput");
}

void Player::InitHUD()
{
	Canvas* _canvas = new Canvas("PlayerHUD", FloatRect(0, 0, 1, 1));

	float _sizeX = 100.0f;
	float _sizeY = 100.0f;
	float _posX = 10.0f;
	float _posY = 10.0f;

	/*Button* _pauseButton = new Button(ObjectData(Vector2f(_posX, _posY), Vector2f(_sizeX, _sizeY), PATH_BUTTONS, IntRect(0, 148, 140, 148)));
	_canvas->AddWidget(_pauseButton);

	_posX = 250.0f;
	_posY = 50.0f;
	_sizeX = 500.0f;
	_sizeY = 150.0f;
	static ProgressBar* _coinsBar = new ProgressBar(ObjectData(Vector2f(_posX, _posY), Vector2f(_sizeX, _sizeY), PATH_COINS_BAR_EMPTY),
													_canvas, PATH_COINS_BAR_FULL, ProgressType::PT_LEFT);
	_coinsBar->SetValue(0.0f);
	_canvas->AddWidget(_coinsBar);
	new Timer("FillCoinsBar", [&]() { _coinsBar->ChangeValue(1); }, seconds(1.0f), true, true);*/

	ProgressBar* _castleBar = new ProgressBar(ObjectData(Vector2f(_posX, _posY), Vector2f(_sizeX, _sizeY), PATH_CASTLE_BAR_EMPTY),
											  _canvas, PATH_CASTLE_BAR_FULL, ProgressType::PT_LEFT);
	//new Timer("FillCastleBar", [&]() { _castleBar->ChangeValue(1); }, seconds(1.0f), true, true);
	_castleBar->SetVisible(false);
	_canvas->AddWidget(_castleBar);

	/*ProgressBar* _loadingBar = new ProgressBar();
	_widgets.push_back(_loadingBar);

	for (Unit* _unit : stats.units)
	{
		Button* _unitButton = new Button();
		new Widget(_unitButton);
	}

	for (Spell* _spell : stats.spells)
	{
		Button* _spellButton = new Button();
		new Widget(_spellButton);
	}*/

}