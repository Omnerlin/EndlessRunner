#pragma once
#include "SFML\Graphics.hpp"
enum class STATE_TYPE
{
	MAIN_MENU,
	GAMELOOP,
	QUIT,
	RESTART
};

class State
{
private:

public:
	virtual void init(sf::RenderWindow &window) = 0;
	virtual void drawObjects(sf::RenderWindow &window) = 0;
	virtual void updateLogic(sf::Time &elapsed) = 0;
	virtual STATE_TYPE handleEvents(sf::Event event) = 0;
	State();
	virtual ~State();
};

