#include "ProjectileManager.h"



void ProjectileManager::fire(sf::Vector2f origin, sf::Vector2f Destination)
{
	for (int i = 0; i < projectiles.size(); i++) {
		if (projectiles[i].getActive() == false) {
			projectiles[i].rect.setPosition(origin);
			projectiles[i].setSpeedOffset(sf::Vector2f(0,0));
			float positionCompareX = Destination.x - origin.x;
			float positionCompareY = Destination.y - origin.y;
			float radian = std::atan2f(positionCompareY, positionCompareX);
			projectiles[i].setDirection(sf::Vector2f(cosf(radian), sinf(radian)));
			projectiles[i].setActive(true);
			break;
		}
	}
}

void ProjectileManager::fire(sf::Vector2f origin, sf::Vector2f Destination, sf::Vector2f offset)
{
	for (int i = 0; i < projectiles.size(); i++) {
		if (projectiles[i].getActive() == false) {
			projectiles[i].rect.setPosition(origin);
			projectiles[i].setSpeedOffset(offset);
			float positionCompareX = Destination.x + projectiles[i].getSpeedOffset().x/120 - origin.x;
			float positionCompareY = Destination.y + projectiles[i].getSpeedOffset().y/120 - origin.y;
			float radian = std::atan2f(positionCompareY, positionCompareX);
			projectiles[i].setDirection(sf::Vector2f(cosf(radian), sinf(radian)));
			projectiles[i].setActive(true);
			break;
		}
	}
}

void ProjectileManager::updateProjectileMovement(float deltaTime)
{
	for (int i = 0; i < projectiles.size(); i++) {
		if (projectiles[i].getActive() == true) {
			projectiles[i].setSpeed(sf::Vector2f(deltaTime * projectiles[i].getBaseMoveSpeed() * projectiles[i].getDirection().x,
				deltaTime * projectiles[i].getBaseMoveSpeed() * projectiles[i].getDirection().y));
			projectiles[i].rect.move(projectiles[i].getSpeed().x, projectiles[i].getSpeed().y);
		}
	}
}

ProjectileManager::ProjectileManager()
{
}


ProjectileManager::~ProjectileManager()
{
}
