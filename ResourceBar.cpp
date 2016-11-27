#include "ResourceBar.h"



void ResourceBar::setCurrentResourceValue(float currentValue)
{
	this->currentResourceValue = currentValue;
}

float ResourceBar::getCurrentResourceValue()
{
	return currentResourceValue;
}

void ResourceBar::setRefillRate(float rate)
{
	this->refillRate = rate;
}

void ResourceBar::setRefillDelay(float delay)
{
	this->refillDelay = delay;
}

float ResourceBar::getRefillDelay()
{
	return refillDelay;
}

float ResourceBar::getMaxLength()
{
	return maxLength;
}

void ResourceBar::setMaxLength(float length)
{
	this->maxLength = length;
}

void ResourceBar::setResourceMax(float max)
{
	this->resourceMax = max;
}

float ResourceBar::getResourceMax()
{
	return resourceMax;
}

ResourceBar::ResourceBar()
{
	shadow.setFillColor(sf::Color(0, 0, 0, 70));
}


ResourceBar::~ResourceBar()
{
}
