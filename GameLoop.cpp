#include "GameLoop.h"
#include <iostream>


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
	player.rect.move(player.moveSpeed.x * deltaTime, player.moveSpeed.y * deltaTime);
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
	}
	if (player.rect.getPosition().x > boundingBox.getSize().x - player.rect.getSize().x) {
		player.rect.setPosition(boundingBox.getSize().x - player.rect.getSize().x, player.rect.getPosition().y);
	}
	if (player.rect.getPosition().y < 0) {
		player.rect.setPosition(player.rect.getPosition().x, 0);
	}
	if (player.rect.getPosition().y > boundingBox.getSize().y - player.rect.getSize().y) {
		player.rect.setPosition(player.rect.getPosition().x, boundingBox.getSize().y - player.rect.getSize().y);
	}
}

void GameLoop::handlePlayerInput(float deltaTime)
{
	player.timeSinceLastFire += deltaTime;

	if (sf::Joystick::isButtonPressed(1, 5) && player.timeSinceLastFire >= player.getFireCooldown()) {
		player.projectileManager.fire(sf::Vector2f(player.rect.getPosition().x + player.rect.getSize().x / 2 - player.projectileManager.projectiles[0].rect.getSize().x/2, player.rect.getPosition().y + player.rect.getSize().y / 2 - player.projectileManager.projectiles[0].rect.getSize().y/2),
			sf::Vector2f(player.reticle.getPosition().x + player.reticle.getRadius() - player.projectileManager.projectiles[0].rect.getSize().x / 2,player.reticle.getPosition().y + player.reticle.getRadius() - player.projectileManager.projectiles[0].rect.getSize().y / 2), player.moveSpeed);
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
				player.moveSpeed = sf::Vector2f(0, 0);
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

void GameLoop::init(sf::RenderWindow &window)
{
	player.rect.setPosition(sf::Vector2f(window.getSize().x / 2, window.getSize().y / 2));
	boundingBox.setPosition(0, 0);
	boundingBox.setSize(window.getDefaultView().getSize());
	pauseOverlay.setFillColor(sf::Color(0, 0, 0, 120));
	pauseOverlay.setSize(sf::Vector2f(window.getSize().x, window.getSize().y));
	pauseText.setFont(gameFont);
	pauseText.setString("PAUSED");
	gameFont.loadFromFile("fonts\\computerFont.ttf");
	pauseText.setPosition(window.getSize().x / 2 - pauseText.getGlobalBounds().width / 2, window.getSize().y / 2 - pauseText.getGlobalBounds().height / 2);
	
}

void GameLoop::drawObjects(sf::RenderWindow &window)
{
	window.clear();
	for (int i = 0; i < player.projectileManager.projectiles.size(); i++) {
		if (player.projectileManager.projectiles[i].getActive() == true) {
			window.draw(player.projectileManager.projectiles[i].rect);
		}
	}
	window.draw(player.rect);
	window.draw(player.reticle);
	if (paused) {
		window.draw(pauseOverlay);
		window.draw(pauseText);
	}
	window.display();
}

void GameLoop::updateLogic(sf::Time &elapsed)
{
	// Everything logic-wise seems to work better when using a timestamp for every iteration, rather than resetting the clock every iteration.

	float deltaTime = elapsed.asSeconds() - timeStamp;
	if (!paused) {
		checkPlayerAgainstBounds();
		handlePlayerInput(deltaTime);
		updatePlayerMovement(deltaTime);
		updatePlayerReticle();
		player.projectileManager.updateProjectileMovement(deltaTime);
		checkProjectileAgainstBounds();
		
	}
	timeStamp = elapsed.asSeconds();
}

void GameLoop::handleEvents(sf::Event event)
{
	if (event.type == sf::Event::JoystickButtonPressed) {
		if (event.joystickButton.joystickId == 1 && event.joystickButton.button == 7) {
			if (paused == false) {
				pause();
			}
			else {
				resume();
			}
		}
	}
}

GameLoop::GameLoop()
{

}


GameLoop::~GameLoop()
{
	delete projectileTexture;
	std::cout << " gameloop destructor called" << std::endl;
}
