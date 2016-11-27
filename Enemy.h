#pragma once
#include "Entity.h"
#include "ProjectileManager.h"
enum class ENEMYTYPES
{
	HOMING,
	STANDARD
};

class Enemy
{
private:
	float health = 100.f;
	float maxHealth = 100.f;
	float fireCooldown = 0.5f;

	sf::Vector2f moveSpeed = sf::Vector2f(100, 100);

	sf::Texture texture;
	sf::Sprite sprite;
	sf::Vector2f spawnDestination;
	bool active = false;
	bool spawning = false;
	ENEMYTYPES type = ENEMYTYPES::STANDARD;

public:
	bool getProjectileManagerActive();
	sf::Color idleColor;
	sf::RectangleShape shadow;
	float timeSinceLastFire = 0.f;
	ProjectileManager projectileManager;
	bool getActive();
	void setActive(bool active);
	bool isSpawning();
	void setSpawning(bool spawning);
	void setSpawnDestination(sf::Vector2f &destination);
	void setEnemyType(ENEMYTYPES type);
	sf::Vector2f getSpawnDestination();
	ENEMYTYPES getEnemyType();
	sf::RectangleShape rect;
	void setHealth(float health);
	float getHealth();
	float getMaxHealth();
	float getFireCooldown();
	void setFireCooldown(float fireCooldown);
	void setMaxHealth(float maxHealth);
	void reset();


	Enemy();
	~Enemy();
};

