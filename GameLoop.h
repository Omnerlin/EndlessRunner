#pragma once
#include "State.h"
#include "Player.h"
class GameLoop : public State
{
private:
	bool paused = false;
	sf::RectangleShape boundingBox;
	sf::RectangleShape pauseOverlay;
	sf::Font gameFont;
	sf::Text pauseText;
	sf::Texture *projectileTexture = new sf::Texture;



	void updatePlayerMovement(float deltaTime);
	void updatePlayerReticle();
	void checkPlayerAgainstBounds();
	void handlePlayerInput(float deltaTime);
	void checkProjectileAgainstBounds();
	void pause();
	void resume();
public:
	STATE_TYPE stateType = STATE_TYPE::GAMELOOP;
	Player player;
	float timeStamp = 0;
	virtual void init(sf::RenderWindow &window);
	virtual void drawObjects(sf::RenderWindow &window);
	virtual void updateLogic(sf::Time &elapsed);
	virtual void handleEvents(sf::Event event);
	GameLoop();
	~GameLoop();
};

