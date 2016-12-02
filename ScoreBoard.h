#pragma once
#include "Entity.h"
#include <iomanip>
#include <iostream>
#include <sstream>
class ScoreBoard
{
private:
	sf::Font scoreFont;

public:
	sf::Text totalScoreText;
	sf::Text timeSurvivedText;
	sf::Text score; 
	sf::Text timeLasted;
	sf::RectangleShape border;
	void updateTextPositions();
	void setScore(int score);
	void setTimeLasted(float timeLasted);
	ScoreBoard();
	~ScoreBoard();
};

