#include "MainMenu.h"



void MainMenu::fade(float deltaTime)
{
	float fadeRate = 0.3;
	float newColorValue;

	if (fadingOut == true) {
		if (fadeRect.getFillColor().a > 0) {
			newColorValue = fadeRect.getFillColor().a - fadeRate * deltaTime;
			if (newColorValue < 0) {
				newColorValue = 0;
			}
			fadeRect.setFillColor(sf::Color(fadeRect.getFillColor().r, fadeRect.getFillColor().g, fadeRect.getFillColor().b, newColorValue));
		}
		if (fadeRect.getFillColor().a == 0) {
			fadingOut = false;
		}
	}
	if (fadingIn == true) {
		if (fadeRect.getFillColor().a < fadeColor.a) {
			newColorValue = fadeRect.getFillColor().a + fadeRate * deltaTime;
			if (newColorValue > fadeColor.a) {
				newColorValue = fadeColor.a;
			}
			fadeRect.setFillColor(sf::Color(fadeRect.getFillColor().r, fadeRect.getFillColor().g, fadeRect.getFillColor().b, newColorValue));
		}
		else if (fadeRect.getFillColor().a == fadeColor.a) {
			std::cout << "FadedIn" << std::endl;
			fadingIn = false;
		}
	}
}


void MainMenu::init(sf::RenderWindow & window)
{
	gameView.setSize(1280, 720);
	gameView.setCenter(1280 / 2, 720 / 2);
	window.setView(gameView);

	boundingBox.setSize(sf::Vector2f(1280,720));
	boundingBox.setOrigin(boundingBox.getSize().x / 2, boundingBox.getSize().y / 2);

	// Background and FadeRect
	background.setSize(sf::Vector2f(gameView.getSize()));
	background.setFillColor(sf::Color(222, 184, 135, 255));
	fadeRect.setSize(sf::Vector2f(gameView.getSize()));
	fadeRect.setFillColor(fadeColor);

	// PlayerRect and PlayerShadow
	playerRect.setSize(sf::Vector2f(150, 150));
	playerRect.setPosition(gameView.getSize().x / 2 - playerRect.getSize().x / 2, gameView.getSize().y / 2 - playerRect.getSize().y / 2);
	playerRectStartPosition = playerRect.getPosition();
	playerShadow.setSize(playerRect.getSize());
	playerShadow.setFillColor(sf::Color(0, 0, 0, 70));
	playerRect.setFillColor(sf::Color(160, 255, 170, 255));

	// Title Text
	gameFont.loadFromFile("fonts\\gameContinue.ttf");
	titleText.setFont(gameFont);
	titleText.setString("Square Game");
	titleText.setCharacterSize(130);
	titleText.setOrigin(titleText.getGlobalBounds().width / 2, titleText.getGlobalBounds().height / 2);
	titleText.setPosition(gameView.getSize().x / 2, gameView.getSize().y / 8);

	// Title Background
	titleBackgroundRect.setSize(sf::Vector2f(gameView.getSize().x, titleText.getGlobalBounds().height * 1.2));
	titleBackgroundRect.setFillColor(sf::Color(0, 0, 0, 180));
	titleBackgroundRect.setOrigin(titleBackgroundRect.getSize().x / 2, titleBackgroundRect.getSize().y / 2);
	titleBackgroundRect.setPosition(titleText.getPosition().x, titleText.getPosition().y);

	// Buttons
	startButton.rect.setSize(sf::Vector2f(startButton.rect.getSize().x, startButton.rect.getSize().y));
	startButton.setPosition(sf::Vector2f(gameView.getSize().x * 0.25, gameView.getSize().y * 0.8));
	startButton.text.setFont(gameFont);
	startButton.text.setString("Start");
	startButton.text.setCharacterSize(60);
	startButton.centerText();

	quitButton.rect.setSize(sf::Vector2f(quitButton.rect.getSize().x, quitButton.rect.getSize().y));
	quitButton.setPosition(sf::Vector2f(gameView.getSize().x * 0.75, gameView.getSize().y * 0.8));
	quitButton.text.setFont(gameFont);
	quitButton.text.setString("Quit");
	quitButton.text.setCharacterSize(60);
	quitButton.centerText();

	startButton.select();
	quitButton.deselect();

	fadingOut = true;
	fadingIn = false;
}

void MainMenu::drawObjects(sf::RenderWindow & window)
{
	window.clear();

	window.draw(background);
	window.draw(playerShadow);
	window.draw(playerRect);
	window.draw(titleBackgroundRect);
	window.draw(titleText);
	window.draw(startButton.rect);
	window.draw(startButton.text);
	window.draw(quitButton.rect);
	window.draw(quitButton.text);

	window.draw(fadeRect);
	window.display();
}

void MainMenu::updateLogic(sf::Time & elapsed)
{
	float deltaTimeMill = elapsed.asMilliseconds() - timeStampMill;
	float deltaTime = elapsed.asSeconds() - timeStamp;

	playerRect.setPosition(playerRect.getPosition().x, playerRectStartPosition.y + (20.f * (sinf(elapsed.asMilliseconds() * 0.002))));
	playerShadow.setPosition(sf::Vector2f(playerRect.getPosition().x + playerRect.getSize().x / 6, playerRect.getPosition().y + playerRect.getSize().y / 6));
	fade(deltaTimeMill);

	if (startButton.getSelected() == true) {
		startButton.bloat(deltaTime);
		quitButton.deflate(deltaTime);
	}
	else if (quitButton.getSelected() == true) {
		quitButton.bloat(deltaTime);
		startButton.deflate(deltaTime);
	}


	timeStampMill = elapsed.asMilliseconds();
	timeStamp = elapsed.asSeconds();
}

STATE_TYPE MainMenu::handleEvents(sf::Event event)
{

	if (event.type == sf::Event::JoystickMoved && event.joystickMove.joystickId == 1 && event.joystickMove.axis == sf::Joystick::Axis::PovX) {
		if (event.joystickMove.position >= 99 || event.joystickMove.position <= -99) {
			//std::cout << "Hit it" << std::endl;
			if (startButton.getSelected() == true) {
				startButton.deselect();
				quitButton.select();
			}
			else if (quitButton.getSelected() == true) {
				quitButton.deselect();
				startButton.select();
			}
		}
	}

	if (event.type == sf::Event::JoystickButtonPressed && event.joystickButton.joystickId == 1 && event.joystickButton.button == 0) {
		//std::cout << event.joystickButton.button << " ID: " << event.joystickButton.joystickId << std::endl;
		if (quitButton.getSelected() == true) {
			return STATE_TYPE::QUIT;
		}
		if (startButton.getSelected() == true) {
			return STATE_TYPE::GAMELOOP;
		}
	}
	
	return STATE_TYPE::MAIN_MENU;
}

MainMenu::MainMenu()
{
}


MainMenu::~MainMenu()
{
}
