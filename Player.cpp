#include "Player.h"



float Player::getTimeInjured()
{
	return timeInjured;
}

bool Player::getInjured()
{
	return injured;
}

void Player::setInjured(bool injured)
{
	this->injured = injured;
	if (injured == true) {
		rect.setFillColor(hurtColor);
	}
	else {
		rect.setFillColor(idleColor);
	}
}

void Player::setTimeInjured(float timeInjured)
{
	this->timeInjured = timeInjured;
}

float Player::getInjuredThreshold()
{
	return injuredThreshold;
}

float Player::getProjectileDamage()
{
	return projectileDamage;
}

void Player::setProjectileDamage(float damage)
{
	this->projectileDamage = damage;
}

float Player::getHealth()
{
	return health;
}

void Player::setHealth(float health)
{
	this->health = health;
}

float Player::getFireCooldown()
{
	return fireCooldown;
}

float Player::getMoveSpeedMod()
{
	return moveSpeedModifier;
}

bool Player::isAlive()
{
	return alive;
}

Player::Player()
{
	rect.setSize(sf::Vector2f(45, 45));
	rect.setFillColor(idleColor);
	shadow.setFillColor(sf::Color(0, 0, 0, 70));
	shadow.setSize(rect.getSize());
	reticle.setRadius(10.f);
	Projectile projectile;
	for (int i = 0; i < 50; i++) {
		projectileManager.projectiles.push_back(projectile);
	}
}


Player::~Player()
{
}
