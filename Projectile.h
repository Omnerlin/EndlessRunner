#pragma once
#include "Entity.h"
enum class PROJECTILE_TYPES
{
	STANDARD,
	HOMING
};

class Projectile
{
private:
	float baseMoveSpeed = 1400.f;
	sf::Vector2f speed = sf::Vector2f(0, 0);
	sf::Vector2f speedOffset = sf::Vector2f(0,0);
	sf::Vector2f direction = sf::Vector2f(0, 0);
	bool active = false;
	PROJECTILE_TYPES type = PROJECTILE_TYPES::STANDARD;

public:
	PROJECTILE_TYPES getProjectileType();
	sf::RectangleShape shadow;
	sf::Vector2f targetDirection = sf::Vector2f(0, 0);
	void setProjectileType(PROJECTILE_TYPES type);
	sf::Vector2f getSpeedOffset();
	void setSpeedOffset(sf::Vector2f offset);
	sf::RectangleShape rect;
	void setDirection(sf::Vector2f &direction);
	bool getActive();
	void setActive(bool active);
	void setSpeed(sf::Vector2f speed);
	float getBaseMoveSpeed();
	void setBaseMoveSpeed(float speed);
	sf::Vector2f getDirection();
	sf::Vector2f getSpeed();
	Projectile();
	~Projectile();
};

