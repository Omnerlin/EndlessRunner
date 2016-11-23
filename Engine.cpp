#include "Engine.h"



void Engine::init()
{
	window.create(sf::VideoMode(1280, 720), "RunnerGame", sf::Style::Titlebar | sf::Style::Close);
	//window.setVerticalSyncEnabled(true);
	//window.setFramerateLimit(120);
}

void Engine::update()
{
	state->init(window);
	engineClock.restart();

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			state->handleEvents(event);
		}

		sf::Time elapsed = engineClock.getElapsedTime();
		state->updateLogic(elapsed);
		state->drawObjects(window);

	}
}

Engine::Engine()
{
}


Engine::~Engine()
{
	delete state;
}
