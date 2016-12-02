#include "ScoreBoard.h"



void ScoreBoard::updateTextPositions()
{
	totalScoreText.setPosition(border.getPosition().x + border.getSize().x / 2 - totalScoreText.getGlobalBounds().width / 2, border.getPosition().y + border.getSize().y / 10);
	score.setPosition(border.getPosition().x + border.getSize().x / 2 - score.getGlobalBounds().width / 2, totalScoreText.getPosition().y + score.getGlobalBounds().height * 2.5);
	timeSurvivedText.setPosition(border.getPosition().x + border.getSize().x / 2 - timeSurvivedText.getGlobalBounds().width / 2, border.getPosition().y + border.getSize().y / 2);
	timeLasted.setPosition(border.getPosition().x + border.getSize().x / 2 - timeLasted.getGlobalBounds().width / 2, timeSurvivedText.getPosition().y + timeLasted.getGlobalBounds().height * 2.5);
	
}

void ScoreBoard::setScore(int score)
{
	this->score.setString(std::to_string(score));
}

void ScoreBoard::setTimeLasted(float timeLasted)
{
	std::stringstream stream;
	stream << std::fixed << std::setprecision(2) << timeLasted;
	std::string s = stream.str();
	this->timeLasted.setString(s + " Minutes");
}

ScoreBoard::ScoreBoard()
{
	border.setSize(sf::Vector2f(300.f, 500.f));
	border.setFillColor(sf::Color(0, 0, 0, 180));
	border.setOutlineColor(sf::Color::White);
	border.setOutlineThickness(10);
	scoreFont.loadFromFile("fonts\\gameContinue.ttf");

	totalScoreText.setFont(scoreFont);
	totalScoreText.setCharacterSize(60);
	timeSurvivedText.setFont(scoreFont);
	timeSurvivedText.setCharacterSize(60);
	score.setFont(scoreFont);
	score.setCharacterSize(50);
	timeLasted.setFont(scoreFont);
	timeLasted.setCharacterSize(50);



	totalScoreText.setString("Score");
	timeSurvivedText.setString("Lasted for" );
	score.setString("1234");
	timeLasted.setString("2.35 Minutes");
	totalScoreText.setStyle(sf::Text::Underlined);
	timeSurvivedText.setStyle(sf::Text::Underlined);
}


ScoreBoard::~ScoreBoard()
{
}
