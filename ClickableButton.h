#pragma once
#include "Entity.h"

class ClickableButton
{
private:
	
	bool selected = false;
	float bloatSize = 1.4;
	float bloatRate = 8;

public:
	sf::RectangleShape rect;
	sf::Text text;
	void setBloatSize(float size);
	float getBloatSize();
	void centerText();
	void setPosition(sf::Vector2f &position);
	void bloat(float deltaTime);
	void deflate(float deltaTime);
	void select();
	void deselect();
	bool getSelected();
	void reset();
	ClickableButton();
	~ClickableButton();
};

