#pragma once
#include "Entity.h"
#include "ProjectileManager.h"

class Player
{
private:
	float moveSpeedModifier = 5;
	sf::Texture texture;
	int health = 100;
	bool alive = true;
	float fireCooldown = 0.1f; // In Seconds!

public:
	float timeSinceLastFire = 0.f;
	ProjectileManager projectileManager;
	sf::Vector2f moveSpeed = sf::Vector2f(0.5, 0.5);
	sf::RectangleShape rect;
	sf::CircleShape reticle;
	sf::Sprite sprite;
	int getHealth();
	float getFireCooldown();
	float getMoveSpeedMod();
	bool isAlive();
	Player();
	~Player();
};

