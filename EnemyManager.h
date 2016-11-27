#pragma once
#include "Enemy.h"


class EnemyManager
{
private:

public:
	std::vector<Enemy> enemies;
	void spawnEnemy(ENEMYTYPES type, sf::RectangleShape &boundingBox);
	void updateEnemyStates(float deltaTime);
	void updateEnemyMovement(float deltaTime);
	void updateEnemyColors(float deltaTime);

	//void updateEnemyProjectileMovement(float deltaTime);
	EnemyManager();
	~EnemyManager();
};

