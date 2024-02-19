#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Map.h"
#include "Macro.h"

using namespace std;
using namespace sf;

class Game
{
	RenderWindow window;
	Map* map;

public:
	Game();
	~Game();

private:
	void Start();
	void Init();
	void Update();
	void UpdateWindow();
	void Stop();

public:
	void Launch();
};