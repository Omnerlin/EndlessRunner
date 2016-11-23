#include "Engine.h"

int main()
{
	Engine engine;
	engine.init();
	engine.update();



	//sf::RenderWindow window(sf::VideoMode(1280, 720), "SFML works!");
	//window.setFramerateLimit(60);
	//sf::CircleShape shape(25.f);
	//shape.setFillColor(sf::Color::Green);
	//shape.setPosition(sf::Vector2f(600, 350));
	//sf::CircleShape shapeTwo(5.f);
	//shapeTwo.setFillColor(sf::Color::Yellow);
	//if (sf::Joystick::isConnected(1)) {
	//	std::cout << "Controller Detected!" << std::endl;
	//	std::cout << "Number of Buttons: " << sf::Joystick::getButtonCount(0) << std::endl;
	//}
	//int count = 0;
	//while (window.isOpen())
	//{
	//	sf::Event event;
	//	while (window.pollEvent(event))
	//	{
	//		if (event.type == sf::Event::Closed)
	//			window.close();
	//			if (event.type == sf::Event::JoystickButtonPressed) {
	//				std::cout << event.joystickButton.button;
	//			}
	//			
	//			//if (event.type == sf::Event::JoystickMoved) {
	//			//	std::cout << event.joystickMove.axis;
	//			//}
	//	}
	//	float x = sf::Joystick::getAxisPosition(1, sf::Joystick::X);
	//	float y = sf::Joystick::getAxisPosition(1, sf::Joystick::Y);
	//	float xTwo = sf::Joystick::getAxisPosition(1, sf::Joystick::U);
	//	float yTwo = sf::Joystick::getAxisPosition(1, sf::Joystick::R);
	//	if (x < -5 || x > 5){
	//	shape.move(x / 8, 0);
	//}
	//	if (y < -5 || y > 5) {
	//		shape.move(0, y / 8);
	//	}
	//	shapeTwo.setPosition((shape.getPosition().x + shape.getRadius() - shapeTwo.getRadius()) + xTwo / 2, (shape.getPosition().y + shape.getRadius() - shapeTwo.getRadius()) + yTwo / 2);
	//	window.clear();
	//	window.draw(shape);
	//	window.draw(shapeTwo);
	//	window.display();
	//	
	//	if (count >= 40) {
	//		std::cout << "X: " << shapeTwo.getPosition().x << " Y:" << shapeTwo.getPosition().y << std::endl;
	//		count = 0;
	//	}
	//	count++;
	//}

	return 0;
}