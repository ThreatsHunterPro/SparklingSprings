#include "Game.h"
#include "TimerManager.h"
#include "InputManager.h"
#include "ActorManager.h"
#include "HUD.h"
#include "Widget.h"
#include "Player.h"

#define PATH_PLAYER "Player.png"

Game::Game()
{
	
}


void Game::Start()
{
	window.create(VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "SparklingSprings");
	TimerManager::GetInstance().SetRenderCallback(bind(&Game::UpdateWindow, this));
	new Timer(this, &Game::Init, seconds(1.0f), true, false);
}

void Game::Init()
{
	Player* _player = new Player("Player", ObjectData(Vector2f(200.0f, 200.0f), Vector2f(150.0f, 150.0f), PATH_PLAYER));
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
		window.draw(*_actor->GetShape());
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
			window.draw(*_widget->GetShape());
		}
	}

	window.display();
}

void Game::Stop()
{
	cout << "A bientôt !" << endl;
}


void Game::Launch()
{
	Start();
	Update();
	Stop();
}