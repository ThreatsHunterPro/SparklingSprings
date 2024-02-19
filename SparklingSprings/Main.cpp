#include "Game.h"
#include "NetworkManager.h"

using namespace std;

int main()
{
	locale::global(locale(""));
	srand(static_cast<unsigned>(time(nullptr)));

	Game _game;
	_game.Launch();
	// test

	/*NetworkManager& _network = NetworkManager::GetInstance();
	_network.PrepareHost();*/

	return 0;
}