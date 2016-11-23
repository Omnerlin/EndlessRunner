#pragma once
#include "SFML\Graphics.hpp"
enum class STATE_TYPE
{
	MAIN_MENU,
	GAMELOOP,

};

class State
{
private:

public:
	virtual void init(sf::RenderWindow &window) = 0;
	virtual void drawObjects(sf::RenderWindow &window) = 0;
	virtual void updateLogic(sf::Time &elapsed) = 0;
	virtual void handleEvents(sf::Event event) = 0;
	State();
	virtual ~State();
};

