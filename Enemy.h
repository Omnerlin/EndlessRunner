#pragma once
#include "Entity.h"
enum class ENEMYTYPES
{
	HOMING,
	STANDARD
};

class Enemy
{
private:
	int health = 100;
	sf::Texture texture;
	sf::Sprite sprite;
	sf::RectangleShape rect;
	bool active = false;
	bool spawning = false;

public:
	void initiate(ENEMYTYPES type);
	Enemy();
	~Enemy();
};

