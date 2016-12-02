#pragma once
#include "State.h"
#include <math.h>
#include "ClickableButton.h"

class MainMenu : public State
{
private:
	float timeStamp = 0;
	float timeStampMill = 0;
	sf::Vector2f scaleFactor;
	sf::View gameView;
	sf::RectangleShape boundingBox;

	// Text for Buttons and Title
	sf::Text titleText;
	sf::Font gameFont;
	sf::RectangleShape titleBackgroundRect;

	// Background to draw on
	sf::RectangleShape background;
	
	// Rectangle to represent the player
	sf::RectangleShape playerRect;
	sf::Vector2f playerRectStartPosition;
	sf::RectangleShape playerShadow;

	// Rectangle to use to fade to white
	sf::RectangleShape fadeRect;
	sf::Color fadeColor = sf::Color::White;
	bool fadingIn;
	bool fadingOut;
	void fade(float deltaTime);
	bool transitioning = false;
	// Buttons
	ClickableButton startButton;
	ClickableButton quitButton;

public:

	STATE_TYPE type = STATE_TYPE::MAIN_MENU;
	virtual void init(sf::RenderWindow &window);
	virtual void drawObjects(sf::RenderWindow &window);
	virtual void updateLogic(sf::Time &elapsed);
	virtual STATE_TYPE handleEvents(sf::Event event);
	MainMenu();
	~MainMenu();
};

