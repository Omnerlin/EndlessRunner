#pragma 
#include "ScoreBoard.h"
#include "State.h"
#include "Player.h"
#include "EnemyManager.h"
#include "ResourceBar.h"
#include "ClickableButton.h"
#include <random>

class GameLoop : public State
{
private:
	ScoreBoard scoreBoard;

	sf::View gameView;
	sf::Vector2f scaleFactor;

	float dPadCooldown = 0.05; // In Seconds
	float timeSinceLastSelect = 0;
	const int NUMBER_OF_ENEMIES = 25;
	bool paused = false;
	bool gameOver = false;
	float enemySpawnCooldown = 2.7f; // In Seconds
	float timeSinceLastSpawn = 1.f;
	
	ClickableButton quitButton;
	ClickableButton resumeButton;
	ClickableButton restartButton;

	ResourceBar healthBar;
	ResourceBar shieldBar;

	sf::RectangleShape backGround;
	sf::RectangleShape boundingBox;
	sf::RectangleShape pauseOverlay;
	sf::Font gameFont;
	sf::Text pauseText;
	EnemyManager enemyManager;

	void updatePlayerState(float deltaTime);
	void handleEnemyProjectilePlayerCollision();
	void updateProjectileMovement(float deltaTime);
	void fireEnemyProjectiles();
	void handlePlayerProjectileCollisions();
	void spawnEnemies();
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
	float generateRandomNumber(int min, int max);
	float timeStamp = 0;
	float timeStampMill = 0;
	virtual void init(sf::RenderWindow &window);
	virtual void drawObjects(sf::RenderWindow &window);
	virtual void updateLogic(sf::Time &elapsed);
	virtual STATE_TYPE handleEvents(sf::Event event);
	GameLoop();
	~GameLoop();
};

