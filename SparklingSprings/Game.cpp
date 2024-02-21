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
	map = new Map(1, Vector2f(window.getSize()));
}

Game::~Game()
{
	delete map;
}


void Game::Start()
{
	window.create(VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "SparklingSprings",Style::Close);
	TimerManager::GetInstance().SetRenderCallback(bind(&Game::UpdateWindow, this));
	new Timer(this, &Game::Init, seconds(1.0f), true, false);
}

void Game::Init()
{
	Player* _player = new Player("Player", ShapeData(Vector2f(200.0f, 200.0f), Vector2f(150.0f, 150.0f), PATH_PLAYER));
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

	vector<Widget*> _widgets = HUD::GetInstance().GetAllWidgets();

	Sort(_widgets);

	for (int _index = (int)_widgets.size(); _index > 0; _index--)
	{
		/*_view.setViewport(_canvas->GetRect())*/;
		window.setView(_view);
		window.draw(*_widgets[_index]->GetDrawable());
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