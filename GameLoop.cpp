#include "GameLoop.h"


void GameLoop::updatePlayerState(float deltaTime)
{
	player.setTimeInjured(player.getTimeInjured() + deltaTime);
	if (player.getTimeInjured() < player.getInjuredThreshold()) {
		player.setInjured(true);
	}
	else {
		player.setInjured(false);
	}
}

void GameLoop::handleEnemyProjectilePlayerCollision()
{
	for (int i = 0; i < enemyManager.enemies.size(); i++) {
		for (int k = 0; k < enemyManager.enemies[i].projectileManager.projectiles.size(); k++) {
			if (enemyManager.enemies[i].projectileManager.projectiles[k].getActive() == true) {
				if (enemyManager.enemies[i].projectileManager.projectiles[k].rect.getGlobalBounds().intersects(player.rect.getGlobalBounds())) {
					enemyManager.enemies[i].projectileManager.projectiles[k].setActive(false);
					if (!player.getInjured()) {
						player.setHealth(player.getHealth() - 5);
						player.setTimeInjured(0);
					}
				}
			}
		}
	}
}

void GameLoop::updateProjectileMovement(float deltaTime)
{
	for (int i = 0; i < enemyManager.enemies.size(); i++) {
			enemyManager.enemies[i].projectileManager.updateProjectileMovement(deltaTime, sf::Vector2f(player.rect.getPosition()));
	}
	player.projectileManager.updateProjectileMovement(deltaTime, sf::Vector2f(player.rect.getPosition()));
}

void GameLoop::fireEnemyProjectiles()
{
	for (int i = 0; i < enemyManager.enemies.size(); i++) {
		if (enemyManager.enemies[i].getActive() && enemyManager.enemies[i].timeSinceLastFire >= enemyManager.enemies[i].getFireCooldown()) {
			enemyManager.enemies[i].projectileManager.fire(enemyManager.enemies[i].rect.getPosition(), player.rect.getPosition());
			enemyManager.enemies[i].timeSinceLastFire = 0.f;
		}
	}
}

void GameLoop::handlePlayerProjectileCollisions()
{
	for (int i = 0; i < enemyManager.enemies.size(); i++) {
		if (enemyManager.enemies[i].getActive() == true) {
			for (int k = 0; k < player.projectileManager.projectiles.size(); k++) {
				if (player.projectileManager.projectiles[k].getActive() == true && player.projectileManager.projectiles[k].rect.getGlobalBounds().intersects(enemyManager.enemies[i].rect.getGlobalBounds())) {
					player.projectileManager.projectiles[k].setActive(false);
					enemyManager.enemies[i].setHealth(enemyManager.enemies[i].getHealth() - player.getProjectileDamage());
					enemyManager.enemies[i].rect.setFillColor(sf::Color::White);
				}
			}
		}
	}
}

void GameLoop::spawnEnemies()
{
	if (timeSinceLastSpawn >= enemySpawnCooldown) {
		ENEMYTYPES typetoSpawn;
		int number = generateRandomNumber(1, 100);
		if (number <= 25) {
			typetoSpawn = ENEMYTYPES::HOMING;
		}
		else {
			typetoSpawn = ENEMYTYPES::STANDARD;
		}

		enemyManager.spawnEnemy(typetoSpawn, boundingBox);
		timeSinceLastSpawn = 0;
	}
}

void GameLoop::updatePlayerMovement(float deltaTime)
{
	float joystickOneX = sf::Joystick::getAxisPosition(1, sf::Joystick::Axis::X);
	float joystickOneY = sf::Joystick::getAxisPosition(1, sf::Joystick::Axis::Y);
	if (joystickOneX < -7 || joystickOneX > 7) {
		player.moveSpeed.x = joystickOneX * player.getMoveSpeedMod();
	}
	else {
		player.moveSpeed.x = 0;
	}
	if (joystickOneY < -7 || joystickOneY > 7) {
		player.moveSpeed.y = joystickOneY * player.getMoveSpeedMod();
	}
	else {
		player.moveSpeed.y = 0;
	}
	//player.moveSpeed = sf::Vector2f(player.moveSpeed.x * deltaTime, player.moveSpeed.y * deltaTime);
	player.rect.move(player.moveSpeed.x * deltaTime, player.moveSpeed.y * deltaTime);
	player.shadow.setPosition(sf::Vector2f(player.rect.getPosition().x + player.rect.getSize().x / 6, player.rect.getPosition().y + player.rect.getSize().y / 6));
}

void GameLoop::updatePlayerReticle()
{
	float joystickTwoX = sf::Joystick::getAxisPosition(1, sf::Joystick::Axis::U);
	float joystickTwoY = sf::Joystick::getAxisPosition(1, sf::Joystick::Axis::R);
	if (joystickTwoX > -7 && joystickTwoX < 7 && joystickTwoY  > -7 && joystickTwoY < 7) {
		joystickTwoX = 100 / 2;
		joystickTwoY = 0;
	}
	player.reticle.setPosition((player.rect.getPosition().x + player.rect.getSize().x / 2 - player.reticle.getRadius()) + joystickTwoX/2, 
		(player.rect.getPosition().y + player.rect.getSize().y / 2 - player.reticle.getRadius()) + joystickTwoY/2);
}

void GameLoop::checkPlayerAgainstBounds()
{

	if (player.rect.getPosition().x < 0) {
		player.rect.setPosition(0, player.rect.getPosition().y);
		player.moveSpeed = sf::Vector2f(0, player.moveSpeed.y);
	}
	if (player.rect.getPosition().x > boundingBox.getSize().x - player.rect.getSize().x) {
		player.rect.setPosition(boundingBox.getSize().x - player.rect.getSize().x, player.rect.getPosition().y);
		player.moveSpeed = sf::Vector2f(0, player.moveSpeed.y);
	}
	if (player.rect.getPosition().y < 0) {
		player.rect.setPosition(player.rect.getPosition().x, 0);
		player.moveSpeed = sf::Vector2f(player.moveSpeed.x, 0);
	}
	if (player.rect.getPosition().y > boundingBox.getSize().y - player.rect.getSize().y) {
		player.rect.setPosition(player.rect.getPosition().x, boundingBox.getSize().y - player.rect.getSize().y);
		player.moveSpeed = sf::Vector2f(player.moveSpeed.x, 0);
	}
}

void GameLoop::handlePlayerInput(float deltaTime)
{
	player.timeSinceLastFire += deltaTime;

	if (sf::Joystick::isButtonPressed(1, 5) && player.timeSinceLastFire >= player.getFireCooldown()) {
		player.projectileManager.fire(sf::Vector2f(player.rect.getPosition().x + player.rect.getSize().x / 2 - player.projectileManager.projectiles[0].rect.getSize().x/2, player.rect.getPosition().y + player.rect.getSize().y / 2 - player.projectileManager.projectiles[0].rect.getSize().y/2),
			sf::Vector2f(player.reticle.getPosition().x + player.reticle.getRadius() - player.projectileManager.projectiles[0].rect.getSize().x / 2,player.reticle.getPosition().y + player.reticle.getRadius() - player.projectileManager.projectiles[0].rect.getSize().y / 2), sf::Vector2f(player.moveSpeed.x /40, player.moveSpeed.y/40));
		player.timeSinceLastFire = 0;
	}
}

void GameLoop::checkProjectileAgainstBounds()
{
	for (int i = 0; i < player.projectileManager.projectiles.size(); i++) {
		if (player.projectileManager.projectiles[i].getActive() == true) {
			if (player.projectileManager.projectiles[i].rect.getPosition().x < 0 - player.projectileManager.projectiles[i].rect.getSize().x
				|| player.projectileManager.projectiles[i].rect.getPosition().x > boundingBox.getSize().x  
				|| player.projectileManager.projectiles[i].rect.getPosition().y < 0 - player.projectileManager.projectiles[i].rect.getSize().y
				|| player.projectileManager.projectiles[i].rect.getPosition().y > boundingBox.getSize().y) {

				player.projectileManager.projectiles[i].setActive(false);
			}
		}
	}

	for (int i = 0; i < enemyManager.enemies.size(); i++) {
		for (int k = 0; k < enemyManager.enemies[i].projectileManager.projectiles.size(); k++) {
			if (enemyManager.enemies[i].projectileManager.projectiles[k].getActive() == true) {
				if (enemyManager.enemies[i].projectileManager.projectiles[k].rect.getPosition().x < 0 - enemyManager.enemies[i].projectileManager.projectiles[k].rect.getSize().x
					|| enemyManager.enemies[i].projectileManager.projectiles[k].rect.getPosition().x > boundingBox.getSize().x
					|| enemyManager.enemies[i].projectileManager.projectiles[k].rect.getPosition().y < 0 - enemyManager.enemies[i].projectileManager.projectiles[k].rect.getSize().y
					|| enemyManager.enemies[i].projectileManager.projectiles[k].rect.getPosition().y > boundingBox.getSize().y) {

					enemyManager.enemies[i].projectileManager.projectiles[k].setActive(false);

				}
			}
		}
	}

}

void GameLoop::pause()
{
	paused = true;
}

void GameLoop::resume()
{
	paused = false;
}

float GameLoop::generateRandomNumber(int min, int max)
{
	/*int randed = std::rand();
	float randomNumber = (randed % max) + min;
	return randomNumber;*/

	std::random_device rd; // obtain a random number from hardware
	std::mt19937 eng(rd()); // seed the generator
	std::uniform_int_distribution<> distr(min, max); // define the range


	return distr(eng); // generate numbers
}

void GameLoop::init(sf::RenderWindow &window)
{
	
	player.rect.setPosition(sf::Vector2f(window.getSize().x / 2, window.getSize().y / 2));
	boundingBox.setPosition(0, 0);
	boundingBox.setSize(window.getDefaultView().getSize());
	backGround.setSize(boundingBox.getSize());
	backGround.setFillColor(sf::Color(222, 184, 135, 255));
	pauseOverlay.setFillColor(sf::Color(0, 0, 0, 120));
	pauseOverlay.setSize(sf::Vector2f(window.getSize().x, window.getSize().y));
	pauseText.setFont(gameFont);
	pauseText.setString("PAUSED");
	pauseText.setCharacterSize(75);
	gameFont.loadFromFile("fonts\\gameContinue.ttf");
	pauseText.setPosition(window.getSize().x / 2 - pauseText.getGlobalBounds().width / 2, window.getSize().y / 2 - pauseText.getGlobalBounds().height / 2);

	// Set up Buttons
	quitButton.setPosition(sf::Vector2f(boundingBox.getSize().x * 0.25, boundingBox.getSize().y * 0.75));
	quitButton.text.setFont(gameFont);
	quitButton.text.setCharacterSize(50);
	quitButton.text.setString("Quit");
	quitButton.centerText();

	resumeButton.setPosition(sf::Vector2f(boundingBox.getSize().x * 0.75, boundingBox.getSize().y * 0.75));
	resumeButton.text.setFont(gameFont);
	resumeButton.text.setCharacterSize(50);
	resumeButton.text.setString("Resume");
	resumeButton.centerText();
	

	//Set up Healthbar
	healthBar.setResourceMax(player.getHealth());
	healthBar.rect.setPosition(boundingBox.getSize().x / 50, boundingBox.getSize().y / 20);
		//healthBar.rect.setOutlineColor(sf::Color::Black);
		//healthBar.rect.setOutlineThickness(5);
	healthBar.rect.setSize(sf::Vector2f(boundingBox.getSize().x / 5, boundingBox.getSize().y / 18));
	healthBar.setMaxLength(healthBar.rect.getSize().x);
	healthBar.backGroundRect.setSize(healthBar.rect.getSize());
	healthBar.backGroundRect.setFillColor(sf::Color(0, 0, 0, 150));
	healthBar.backGroundRect.setPosition(healthBar.rect.getPosition());
	healthBar.backGroundRect.setOutlineColor(sf::Color::Black);
	healthBar.backGroundRect.setOutlineThickness(5);
	healthBar.rect.setFillColor(sf::Color(200,100,100,255));
	healthBar.shadow.setSize(healthBar.rect.getSize());
	healthBar.shadow.setPosition(sf::Vector2f(healthBar.rect.getPosition().x + healthBar.rect.getSize().x / 6, healthBar.rect.getPosition().y + healthBar.rect.getSize().y / 6));


	// Populate Enemy Manager
	Enemy enemy;
	for (int i = 0; i < NUMBER_OF_ENEMIES; i++) {
		enemyManager.enemies.push_back(enemy);
	}

}

void GameLoop::drawObjects(sf::RenderWindow &window)
{
	window.clear();
	window.draw(backGround);
	for (int i = 0; i < player.projectileManager.projectiles.size(); i++) {
		if (player.projectileManager.projectiles[i].getActive() == true) {
			window.draw(player.projectileManager.projectiles[i].shadow);
			window.draw(player.projectileManager.projectiles[i].rect);
		}
	}
	// Draw Enemies
	for (int i = 0; i < enemyManager.enemies.size(); i++) {
		if (enemyManager.enemies[i].getActive() == true || enemyManager.enemies[i].isSpawning() == true) {
			window.draw(enemyManager.enemies[i].shadow);
			window.draw(enemyManager.enemies[i].rect);
		}
		// Draw the projectiles of each enemy
		for (int k = 0; k < enemyManager.enemies[i].projectileManager.projectiles.size(); k++) {
			if (enemyManager.enemies[i].projectileManager.projectiles[k].getActive() == true) {
				window.draw(enemyManager.enemies[i].projectileManager.projectiles[k].shadow);
				window.draw(enemyManager.enemies[i].projectileManager.projectiles[k].rect);
				
			}
		}
	}
	window.draw(player.shadow);
	window.draw(player.rect);
	window.draw(player.reticle);
	//window.draw(healthBar.shadow);
	window.draw(healthBar.backGroundRect);
	window.draw(healthBar.rect);
	if (paused) {
		window.draw(pauseOverlay);
		window.draw(pauseText);
		window.draw(quitButton.rect);
		window.draw(quitButton.text);
		window.draw(resumeButton.rect);
		window.draw(resumeButton.text);
	}
	window.display();
}

void GameLoop::updateLogic(sf::Time &elapsed)
{
	// Everything logic-wise seems to work better when using a timestamp for every iteration, rather than resetting the clock every iteration.

	float deltaTime = elapsed.asSeconds() - timeStamp;

	if (!paused) {
		timeSinceLastSpawn += deltaTime;


		spawnEnemies();
		updatePlayerMovement(deltaTime);
		checkPlayerAgainstBounds();
		handlePlayerInput(deltaTime);
		updatePlayerReticle();
		fireEnemyProjectiles();
		updateProjectileMovement(deltaTime);
		checkProjectileAgainstBounds();
		enemyManager.updateEnemyMovement(deltaTime);
		handlePlayerProjectileCollisions();
		handleEnemyProjectilePlayerCollision();
		updatePlayerState(deltaTime);
		if (player.getHealth() <= 0) { player.setHealth(0); }
		healthBar.setCurrentResourceValue(player.getHealth());
		healthBar.rect.setSize(sf::Vector2f(healthBar.getMaxLength() * (healthBar.getCurrentResourceValue() / healthBar.getResourceMax()), healthBar.rect.getSize().y));
		enemyManager.updateEnemyStates(deltaTime);
		enemyManager.updateEnemyColors(deltaTime);
	}
	if (paused) {
		if (resumeButton.getSelected() == true) {
			resumeButton.bloat(deltaTime);
		}
		else if (resumeButton.getSelected() == false) {
			resumeButton.deflate(deltaTime);
		}
		if (quitButton.getSelected() == true) {
			quitButton.bloat(deltaTime);
		}
		else if (quitButton.getSelected() == false) {
			quitButton.deflate(deltaTime);
		}
		timeSinceLastSelect += deltaTime;
	}

	timeStamp = elapsed.asSeconds();
}

STATE_TYPE GameLoop::handleEvents(sf::Event event)
{
	// Pause the game
	if (event.type == sf::Event::JoystickButtonPressed) {
		if (event.joystickButton.joystickId == 1 && event.joystickButton.button == 7) {
			if (paused == false) {
				pause();
				resumeButton.select();
				quitButton.deselect();
			}
			else {
				resume();
				quitButton.reset();
				resumeButton.reset();
			}
		}
	}

	if (paused && timeSinceLastSelect >= dPadCooldown && event.type == sf::Event::JoystickMoved && event.joystickMove.joystickId == 1 && event.joystickMove.axis == sf::Joystick::Axis::PovX) {
		if (event.joystickMove.position >= 99 || event.joystickMove.position <= -99) {
			//std::cout << "Hit it" << std::endl;
			if (resumeButton.getSelected() == true) {
				resumeButton.deselect();
				quitButton.select();
			}
			else if (quitButton.getSelected() == true) {
				quitButton.deselect();
				resumeButton.select();
			}
			timeSinceLastSelect = 0;
		}
	}

	if (paused && event.type == sf::Event::JoystickButtonPressed && event.joystickButton.joystickId == 1 && event.joystickButton.button == 0) {
		//std::cout << event.joystickButton.button << " ID: " << event.joystickButton.joystickId << std::endl;
		if (quitButton.getSelected() == true) {
			return STATE_TYPE::QUIT;
		}
		if (resumeButton.getSelected() == true) {
			resume();
		}
	}

	return STATE_TYPE::GAMELOOP;
}

GameLoop::GameLoop()
{

}


GameLoop::~GameLoop()
{
	delete projectileTexture;
	std::cout << "gameloop destructor called" << std::endl;
}
