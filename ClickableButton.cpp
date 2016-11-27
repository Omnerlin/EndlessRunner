#include "ClickableButton.h"



void ClickableButton::setBloatSize(float size)
{
	this->bloatSize = size;
}

float ClickableButton::getBloatSize()
{
	return bloatSize;
}

void ClickableButton::centerText()
{
	text.setOrigin(text.getGlobalBounds().width / 2, text.getGlobalBounds().height / 2);
	text.setPosition(rect.getPosition().x, rect.getPosition().y - text.getGlobalBounds().height / 4);
}

void ClickableButton::setPosition(sf::Vector2f & position)
{
	rect.setPosition(position);
	text.setPosition(position.x - text.getGlobalBounds().width, position.y);
}

void ClickableButton::bloat(float deltaTime)
{
	if (rect.getScale().x < bloatSize && rect.getScale().y < bloatSize) {
		rect.setScale(rect.getScale().x + bloatRate * deltaTime, rect.getScale().y + bloatRate * deltaTime);
		text.setScale(text.getScale().x + bloatRate * deltaTime, text.getScale().y + bloatRate * deltaTime);
	}
	else if (rect.getScale().x > bloatSize && rect.getScale().y > bloatSize) {
		rect.setScale(bloatSize, bloatSize);
		text.setScale(bloatSize, bloatSize);
	}
}

void ClickableButton::deflate(float deltaTime)
{
	if (rect.getScale().x > 1 && rect.getScale().y > 1) {
		rect.setScale(rect.getScale().x - bloatRate * deltaTime, rect.getScale().y - bloatRate * deltaTime);
		text.setScale(text.getScale().x - bloatRate * deltaTime, text.getScale().y - bloatRate * deltaTime);
	}
	else if (rect.getScale().x < 1 && rect.getScale().y < 1) {
		rect.setScale(1, 1);
		text.setScale(1, 1);
	}
}

void ClickableButton::select()
{
	selected = true;
}

void ClickableButton::deselect()
{
	selected = false;
}

bool ClickableButton::getSelected()
{
	return selected;
}

void ClickableButton::reset()
{
	rect.setScale(1, 1);
	text.setScale(1, 1);
}


ClickableButton::ClickableButton()
{
	rect.setSize(sf::Vector2f(200.f, 125.f));
	rect.setFillColor(sf::Color(184, 87, 80, 255));
	rect.setPosition(0.f, 0.f);
	rect.setOrigin(rect.getPosition().x + rect.getGlobalBounds().width / 2, rect.getPosition().y + rect.getGlobalBounds().height / 2);
}


ClickableButton::~ClickableButton()
{
}
