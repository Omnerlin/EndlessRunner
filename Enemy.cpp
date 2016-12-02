#include "Enemy.h"




bool Enemy::getProjectileManagerActive()
{
	for (int i = 0; i < projectileManager.projectiles.size(); i++) {
		if (projectileManager.projectiles[i].getActive()) {
			return true;
		}
	}
	return false;
}

bool Enemy::getActive()
{
	return active;
}

void Enemy::setActive(bool active)
{
	this->active = active;
}

bool Enemy::isSpawning()
{
	return spawning;
}

void Enemy::setSpawning(bool spawning)
{
	this->spawning = spawning;
}

void Enemy::setSpawnDestination(sf::Vector2f & destination)
{
	spawnDestination = destination;
}

void Enemy::setEnemyType(ENEMYTYPES type)
{
	this->type = type;
}

sf::Vector2f Enemy::getSpawnDestination()
{
	return spawnDestination;
}

ENEMYTYPES Enemy::getEnemyType()
{
	return type;
}

void Enemy::setHealth(float health)
{
	this->health = health;
}

float Enemy::getHealth()
{
	return health;
}

float Enemy::getMaxHealth()
{
	return maxHealth;
}

float Enemy::getFireCooldown()
{
	return fireCooldown;
}

void Enemy::setFireCooldown(float fireCooldown)
{
	this->fireCooldown = fireCooldown;
}

void Enemy::setMaxHealth(float maxHealth)
{
	this->maxHealth = maxHealth;
}

void Enemy::reset()
{
	// Resets the enemy in the array. Usually do this when the enemy is killed.
	setActive(false);
	setSpawning(false);
}

Enemy::Enemy()
{
	rect.setSize(sf::Vector2f(40, 40));
	shadow.setSize(rect.getSize());
	shadow.setFillColor(sf::Color(0, 0, 0, 70));
	Projectile projectile;
	for (int i = 0; i < 30; i++) {
		projectileManager.projectiles.push_back(projectile);
	}
	
}


Enemy::~Enemy()
{
}
