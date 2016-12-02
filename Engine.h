#pragma once
#include "GameLoop.h"
#include "MainMenu.h"

class Engine
{
private:
	sf::RenderWindow window;
	State *state = new MainMenu;
	sf::Clock engineClock;
	STATE_TYPE currentState;
public:
	void init();
	void update();
	void switchStates(STATE_TYPE state);

	Engine();
	~Engine();
};

