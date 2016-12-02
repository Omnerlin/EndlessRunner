#include "Engine.h"



void Engine::init()
{
	//window.create(sf::VideoMode(1280, 720), "RunnerGame", sf::Style::Titlebar | sf::Style::Close);
	window.create(sf::VideoMode::getDesktopMode(), "RunnerGame", sf::Style::Titlebar | sf::Style::Close | sf::Style::Fullscreen);
	//window.setVerticalSyncEnabled(true);
	//window.setFramerateLimit(120);
}

void Engine::update()
{
	state->init(window);
	engineClock.restart();
	STATE_TYPE tempState = STATE_TYPE::MAIN_MENU;
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

			tempState = state->handleEvents(event);
		}
		if (tempState != currentState) {
			if (tempState == STATE_TYPE::QUIT) {
				window.close();
			}
			else if (tempState == STATE_TYPE::RESTART) {
				delete this->state;
				if (currentState == STATE_TYPE::GAMELOOP) {
					this->state = new GameLoop;
					tempState = STATE_TYPE::GAMELOOP;
				}
				else {
					this->state = new MainMenu;
					tempState = STATE_TYPE::MAIN_MENU;
				}
				engineClock.restart();
				this->state->init(window);
				
			}
			else {
				switchStates(tempState);
				engineClock.restart();
				state->init(window);
			}
		}
		sf::Time elapsed = engineClock.getElapsedTime();
		state->updateLogic(elapsed); 
		state->drawObjects(window);
	}
}

void Engine::switchStates(STATE_TYPE state)
{
	delete this->state;
	if (state == STATE_TYPE::GAMELOOP) {
		this->state = new GameLoop;
		this->currentState = state;
	}
	else if (state == STATE_TYPE::MAIN_MENU) {
		this->state = new MainMenu;
		this->currentState = state;
	}
}

Engine::Engine()
{
}


Engine::~Engine()
{
	delete state;
}
