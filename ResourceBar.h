#pragma once
#include "Entity.h"

class ResourceBar
{
private:
	float resourceMax;
	float currentResourceValue;
	float refillRate; // Value per Second
	float refillDelay;
	float maxLength;
public:
	sf::RectangleShape rect;
	sf::RectangleShape backGroundRect;
	sf::RectangleShape shadow;
	void setCurrentResourceValue(float currentValue);
	float getCurrentResourceValue();
	void setRefillRate(float rate);
	void setRefillDelay(float delay);
	float getRefillDelay();
	float getMaxLength();
	void setMaxLength(float length);
	void setResourceMax(float max);
	float getResourceMax();


	ResourceBar();
	~ResourceBar();
};

