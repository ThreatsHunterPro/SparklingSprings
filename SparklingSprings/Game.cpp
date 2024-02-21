#include "Game.h"
#include "TimerManager.h"
#include "InputManager.h"
#include "ActorManager.h"
#include "HUD.h"
#include "Widget.h"
#include "Player.h"

#define PATH_PLAYER "Player.png"
#define FONT "Assets/Fonts/Font.ttf"

Game::Game()
{
	//map = new Map();
}

Game::~Game()
{
	//delete map;
}


void Game::Start()
{
	window.create(VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "SparklingSprings");
	TimerManager::GetInstance().SetRenderCallback(bind(&Game::UpdateWindow, this));
	new Timer(this, &Game::Init, seconds(1.0f), true, false);
}

void Game::Init()
{
	//map->Init(Vector2f(window.getSize()));

	Player* _player = new Player("Player", ShapeData(Vector2f(300.0f, 500.0f), Vector2f(100.0f, 100.0f), PATH_PLAYER));
	_player->Init();
}

void Game::Update()
{
	while (window.isOpen())
	{
		TimerManager::GetInstance().Update();
		if (!InputManager::GetInstance().Update(window)) break;
		ActorManager::GetInstance().Update();
	}
}

void Game::UpdateWindow()
{
	window.clear();

	// Game
	const View& _defaultView = window.getDefaultView();
	window.setView(_defaultView);
	for (Actor* _actor : ActorManager::GetInstance().GetAllValues())
	{
		window.draw(*_actor->GetDrawable());
	}

	// UI
	View _view = _defaultView;
	for (Canvas* _canvas : HUD::GetInstance().GetAllValues())
	{
		if (!_canvas->IsVisible()) continue;

		_view.setViewport(_canvas->GetRect());
		window.setView(_view);

		for (Widget* _widget : _canvas->GetWidgets()) 
		{
			if (!_widget->IsVisible()) continue;
			window.draw(*_widget->GetDrawable());
		}
	}

	window.display();
}

void Game::Stop()
{
	cout << "A bient�t !" << endl;
}


void Game::Launch()
{
	Start();
	Update();
	Stop();
}