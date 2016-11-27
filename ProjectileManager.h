#pragma once
#include <vector>
#include "Projectile.h"


class ProjectileManager
{
private:
	

public:
	void setProjectileType(PROJECTILE_TYPES type);
	void fire(sf::Vector2f origin, sf::Vector2f Destination);
	void ProjectileManager::fire(sf::Vector2f origin, sf::Vector2f Destination, sf::Vector2f offset);
	void updateProjectileMovement(float deltaTime, sf::Vector2f &destination);
	std::vector<Projectile> projectiles;
	ProjectileManager();
	~ProjectileManager();
};

