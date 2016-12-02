#pragma once
#include "Entity.h"

class Shield
{
private:
	
	sf::Color shieldColor = sf::Color(0, 191, 255, 125);
	float maxHealth = 100.f;
	float health = 100.f;
	bool active = false;
	sf::Vector2f defaultSize;
	float bloatRate = 9.5f;

	float timeInactive = 0.f;
	float rechargeCooldown = 2.5f;
	float rechargeRate = 20.f;


public:
	void updateColor();
	float getTimeInactive();
	void setTimeInactive(float timeInactive);
	void recharge(float deltaTime);
	sf::RectangleShape rect;
	float getHealth();
	void setHealth(float health);
	bool getActive();
	void setActive(bool active);
	float getMaxHealth();
	void setMaxHealth(float maxHealth);
	void bloat(float deltaTime);
	void deflate(float deltaTime);
	sf::Vector2f getDefaultSize();
	void setDefaultSize(sf::Vector2f &size);
	Shield();
	~Shield();
};

