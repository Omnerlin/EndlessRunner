#include "EnemyManager.h"
#include "randomNumbers.h"


void EnemyManager::spawnEnemy(ENEMYTYPES type, sf::RectangleShape &boundingBox)
{
	// Spawn the first available enemy

	for (int i = 0; i < enemies.size(); i++) {
		if (enemies[i].getActive() == false && enemies[i].isSpawning() == false && !enemies[i].getProjectileManagerActive()) {
			enemies[i].setEnemyType(type);
			if (type == ENEMYTYPES::STANDARD) {
				// We want standard enemies to spawn from the right side of the screen.
				enemies[i].rect.setPosition(generateRandomFloat(boundingBox.getSize().x * 2, boundingBox.getSize().x * 2), 
					generateRandomFloat(enemies[i].rect.getSize().y * 2.5, boundingBox.getSize().y - enemies[i].rect.getSize().y * 2.5));

				// We want to set the Spawn destination Y coordinate to be close to the position Y coordinate so there's no weird fly-ins.
				enemies[i].setSpawnDestination(sf::Vector2f(generateRandomFloat(boundingBox.getSize().x / 2.2, boundingBox.getSize().x - enemies[i].rect.getSize().x * 2.5), 
					generateRandomFloat(enemies[i].rect.getPosition().y - enemies[i].rect.getSize().y * 2.5, enemies[i].rect.getPosition().y + enemies[i].rect.getSize().y * 2.5)));

				enemies[i].idleColor = sf::Color(150, 150, 150);
				enemies[i].rect.setFillColor(enemies[i].idleColor);
				enemies[i].projectileManager.setProjectileType(PROJECTILE_TYPES::STANDARD);
				enemies[i].setMaxHealth(60);
				enemies[i].setHealth(enemies[i].getMaxHealth());
				enemies[i].setActive(false);
				enemies[i].setSpawning(true);
				//std::cout << "Enemy Spawned at X: " << enemies[i].getSpawnDestination().x << " Y: " << enemies[i].getSpawnDestination().y << std::endl;
				break;
			}
			if (type == ENEMYTYPES::HOMING) {
				// We want standard enemies to spawn from the right side of the screen.
				enemies[i].rect.setPosition(generateRandomFloat(boundingBox.getSize().x * 2, boundingBox.getSize().x * 2),
					generateRandomFloat(enemies[i].rect.getSize().y * 2.5, boundingBox.getSize().y - enemies[i].rect.getSize().y * 2.5));

				// We want to set the Spawn destination Y coordinate to be close to the position Y coordinate so there's no weird fly-ins.
				enemies[i].setSpawnDestination(sf::Vector2f(generateRandomFloat(boundingBox.getSize().x / 2.2, boundingBox.getSize().x - enemies[i].rect.getSize().x * 2.5),
					generateRandomFloat(enemies[i].rect.getPosition().y - enemies[i].rect.getSize().y * 2.5, enemies[i].rect.getPosition().y + enemies[i].rect.getSize().y * 2.5)));

				enemies[i].idleColor = sf::Color::Magenta;
				enemies[i].rect.setFillColor(enemies[i].idleColor);

				enemies[i].projectileManager.setProjectileType(PROJECTILE_TYPES::HOMING);
				enemies[i].setMaxHealth(100);
				enemies[i].setHealth(enemies[i].getMaxHealth());
				enemies[i].setActive(false);
				enemies[i].setSpawning(true);
				//std::cout << "Enemy Spawned at X: " << enemies[i].getSpawnDestination().x << " Y: " << enemies[i].getSpawnDestination().y << std::endl;
				break;
			}
		}
	}
}

void EnemyManager::updateEnemyStates(float deltaTime)
{
	for (int i = 0; i < enemies.size(); i++) {
		if (enemies[i].isSpawning() && enemies[i].rect.getPosition().x <= enemies[i].getSpawnDestination().x + enemies[i].rect.getSize().x * 2) {
			//enemies[i].setSpawning(false);
			enemies[i].setActive(true);
		}
		if (enemies[i].getActive() == true) {
			enemies[i].timeSinceLastFire += deltaTime;
		}
		if (enemies[i].getHealth() <= 0) {
			enemies[i].reset();
		}


	}
}

void EnemyManager::updateEnemyMovement(float deltaTime)
{
	for (int i = 0; i < enemies.size(); i++) {
		if (enemies[i].isSpawning()) {
			enemies[i].rect.move(((enemies[i].getSpawnDestination().x - enemies[i].rect.getPosition().x) * 2) * deltaTime, ((enemies[i].getSpawnDestination().y - enemies[i].rect.getPosition().y) * 2) * deltaTime);
			enemies[i].shadow.setPosition(sf::Vector2f(enemies[i].rect.getPosition().x + enemies[i].rect.getSize().x / 6, enemies[i].rect.getPosition().y + enemies[i].rect.getSize().y / 6));
		}
	}
}

void EnemyManager::updateEnemyColors(float deltaTime)
{
	float newRed;
	float newBlue;
	float newGreen;
	float colorChangeRate = 0.03;
	for (int i = 0; i < enemies.size(); i++) {
		if (enemies[i].getActive() == true) {
			if (enemies[i].rect.getFillColor() != enemies[i].idleColor) {
				if (enemies[i].rect.getFillColor().r > enemies[i].idleColor.r) {
					newRed = enemies[i].rect.getFillColor().r - colorChangeRate * deltaTime;
					if (newRed < 0) {
						newRed = 0;
					}
					enemies[i].rect.setFillColor(sf::Color(newRed, enemies[i].rect.getFillColor().g, enemies[i].rect.getFillColor().b, 255));
				}
				 if (enemies[i].rect.getFillColor().r < enemies[i].idleColor.r) {
					enemies[i].rect.setFillColor(sf::Color(enemies[i].idleColor.r, enemies[i].rect.getFillColor().g, enemies[i].rect.getFillColor().b, 255));
				}


				if (enemies[i].rect.getFillColor().g > enemies[i].idleColor.g) {
					newGreen = enemies[i].rect.getFillColor().g - colorChangeRate * deltaTime;
					if (newGreen < 0) {
						newGreen = 0;
					}
					enemies[i].rect.setFillColor(sf::Color(enemies[i].rect.getFillColor().r, newGreen, enemies[i].rect.getFillColor().b, 255));
				}
				if (enemies[i].rect.getFillColor().g < enemies[i].idleColor.g) {
					enemies[i].rect.setFillColor(sf::Color(enemies[i].rect.getFillColor().r, enemies[i].idleColor.g, enemies[i].rect.getFillColor().b, 255));
				}


				if (enemies[i].rect.getFillColor().b > enemies[i].idleColor.b) {
					newBlue = enemies[i].rect.getFillColor().g - colorChangeRate * deltaTime;
					if (newBlue < 0) {
						newBlue = 0;
					}

					enemies[i].rect.setFillColor(sf::Color(enemies[i].rect.getFillColor().r, enemies[i].rect.getFillColor().g, newBlue, 255));
				}
				if (enemies[i].rect.getFillColor().b < enemies[i].idleColor.b) {

					enemies[i].rect.setFillColor(sf::Color(enemies[i].rect.getFillColor().r, enemies[i].rect.getFillColor().g, enemies[i].idleColor.b, 255));
				}

			}
		}
	}
}



EnemyManager::EnemyManager()
{
}


EnemyManager::~EnemyManager()
{
}
