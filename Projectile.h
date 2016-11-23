#pragma once
#include "Entity.h"

class Projectile
{
private:
	float baseMoveSpeed = 1400.f;
	sf::Vector2f speed = sf::Vector2f(0, 0);
	sf::Vector2f speedOffset = sf::Vector2f(0,0);
	sf::Texture texture;
	sf::Sprite sprite;
	sf::Vector2f direction = sf::Vector2f(0, 0);
	bool active = false;

public:
	sf::Vector2f getSpeedOffset();
	void setSpeedOffset(sf::Vector2f offset);
	sf::RectangleShape rect;
	void setDirection(sf::Vector2f &direction);
	bool getActive();
	void setActive(bool active);
	void setSpeed(sf::Vector2f speed);
	float getBaseMoveSpeed();
	sf::Vector2f getDirection();
	sf::Vector2f getSpeed();
	Projectile();
	~Projectile();
};

