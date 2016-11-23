#include "Player.h"



int Player::getHealth()
{
	return health;
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
	rect.setSize(sf::Vector2f(25, 25));
	reticle.setRadius(10.f);
	Projectile projectile;
	for (int i = 0; i < 50; i++) {
		projectileManager.projectiles.push_back(projectile);
	}
}


Player::~Player()
{
}
