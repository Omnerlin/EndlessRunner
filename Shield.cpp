#include "Shield.h"



void Shield::bloat(float deltaTime)
{
	rect.setScale(rect.getScale().x + bloatRate * deltaTime, rect.getScale().y + bloatRate * deltaTime);
	if (rect.getScale().x > 1 || rect.getScale().y > 1) {
		rect.setScale(1, 1);
	}
}

void Shield::deflate(float deltaTime)
{
	rect.setScale(rect.getScale().x - bloatRate * deltaTime, rect.getScale().y - bloatRate * deltaTime);
	if (rect.getScale().x < 0 || rect.getScale().y < 0) {
		rect.setScale(0, 0);
	}
}



void Shield::updateColor()
{
	rect.setFillColor(sf::Color(255 - rect.getFillColor().b, shieldColor.g * (health / maxHealth), shieldColor.b * (health / maxHealth), shieldColor.a));
}

float Shield::getTimeInactive()
{
	return timeInactive;
}

void Shield::setTimeInactive(float timeInactive)
{
	this->timeInactive = timeInactive;
}

void Shield::recharge(float deltaTime)
{
	if (timeInactive >= rechargeCooldown) {
		health += rechargeRate * deltaTime;
		if (health > maxHealth) {
			health = maxHealth;
		}
	}
}

float Shield::getHealth()
{
	return health;
}

void Shield::setHealth(float health)
{
	this->health = health;
}

bool Shield::getActive()
{
	return active;
}

void Shield::setActive(bool active)
{
	this->active = active;
}

float Shield::getMaxHealth()
{
	return maxHealth;
}

void Shield::setMaxHealth(float maxHealth)
{
	this->maxHealth = maxHealth;
}

sf::Vector2f Shield::getDefaultSize()
{
	return defaultSize;
}

void Shield::setDefaultSize(sf::Vector2f & size)
{
	this->defaultSize = size;
}

Shield::Shield()
{
	rect.setFillColor(shieldColor);
	health = maxHealth;
}


Shield::~Shield()
{
}
