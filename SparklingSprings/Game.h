#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

class Game
{
	RenderWindow window;

public:
	Game();

private:
	void Start();
	void Init();
	void Update();
	void UpdateWindow();
	void Stop();

public:
	void Launch();
};