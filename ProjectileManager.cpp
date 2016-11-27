#include "ProjectileManager.h"



void ProjectileManager::setProjectileType(PROJECTILE_TYPES type)
{
	for (int i = 0; i < projectiles.size(); i++) {
		projectiles[i].setProjectileType(type);
		if (type == PROJECTILE_TYPES::STANDARD) {
			projectiles[i].rect.setFillColor(sf::Color::White);
		}
		else if (type == PROJECTILE_TYPES::HOMING) {
			projectiles[i].rect.setFillColor(sf::Color::Yellow);
		}
	}
}

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
			float positionCompareX = Destination.x + projectiles[i].getSpeedOffset().x - origin.x;
			float positionCompareY = Destination.y + projectiles[i].getSpeedOffset().y - origin.y;
			float radian = std::atan2f(positionCompareY, positionCompareX);
			projectiles[i].setDirection(sf::Vector2f(cosf(radian), sinf(radian)));
			projectiles[i].setActive(true);
			break;
		}
	}
}

void ProjectileManager::updateProjectileMovement(float deltaTime, sf::Vector2f &destination)
{
	for (int i = 0; i < projectiles.size(); i++) {
		if (projectiles[i].getActive() == true) {
			if (projectiles[i].getProjectileType() == PROJECTILE_TYPES::STANDARD) {
				projectiles[i].setSpeed(sf::Vector2f(deltaTime * projectiles[i].getBaseMoveSpeed() * projectiles[i].getDirection().x,
					deltaTime * projectiles[i].getBaseMoveSpeed() * projectiles[i].getDirection().y));
				projectiles[i].rect.move(projectiles[i].getSpeed().x, projectiles[i].getSpeed().y);
				projectiles[i].shadow.setPosition(sf::Vector2f(projectiles[i].rect.getPosition().x + projectiles[i].rect.getSize().x / 6, projectiles[i].rect.getPosition().y + projectiles[i].rect.getSize().y / 6));
			}
			else if (projectiles[i].getProjectileType() == PROJECTILE_TYPES::HOMING) {
				float positionCompareX = (destination.x + projectiles[i].getSpeedOffset().x - projectiles[i].rect.getPosition().x) * deltaTime;
				float positionCompareY = (destination.y + projectiles[i].getSpeedOffset().y - projectiles[i].rect.getPosition().y) * deltaTime;
				float radian = std::atan2f(positionCompareY, positionCompareX);
				projectiles[i].targetDirection = (sf::Vector2f(cosf(radian), sinf(radian)));

				if (projectiles[i].getDirection().x < projectiles[i].targetDirection.x) {
					projectiles[i].setDirection(sf::Vector2f(projectiles[i].getDirection().x + 0.7 * deltaTime, projectiles[i].getDirection().y));
				}
				if (projectiles[i].getDirection().x > projectiles[i].targetDirection.x) {
					projectiles[i].setDirection(sf::Vector2f(projectiles[i].getDirection().x - 0.7 * deltaTime, projectiles[i].getDirection().y));
				}
				if (projectiles[i].getDirection().y < projectiles[i].targetDirection.y) {
					projectiles[i].setDirection(sf::Vector2f(projectiles[i].getDirection().x, projectiles[i].getDirection().y + 0.7 * deltaTime));
				}
				if (projectiles[i].getDirection().y > projectiles[i].targetDirection.y) {
					projectiles[i].setDirection(sf::Vector2f(projectiles[i].getDirection().x, projectiles[i].getDirection().y - 0.7 * deltaTime));
				}
				

				projectiles[i].setSpeed(sf::Vector2f(deltaTime * projectiles[i].getBaseMoveSpeed() * projectiles[i].getDirection().x,
					deltaTime * projectiles[i].getBaseMoveSpeed() * projectiles[i].getDirection().y));
				projectiles[i].rect.move(projectiles[i].getSpeed().x, projectiles[i].getSpeed().y);
				projectiles[i].shadow.setPosition(sf::Vector2f(projectiles[i].rect.getPosition().x + projectiles[i].rect.getSize().x / 6, projectiles[i].rect.getPosition().y + projectiles[i].rect.getSize().y / 6));

			}
		}
	}
}

ProjectileManager::ProjectileManager()
{
}


ProjectileManager::~ProjectileManager()
{
}
