#include "ScorePanel.h"
#include "GameManager.h"
#include "RessourceManager.h"

ScorePanel::ScorePanel(sf::Vector2f pos) : Entity(pos)
{
	Panel = new sf::RectangleShape(sf::Vector2f(200, 70));
	Panel->setOutlineThickness(-5);
	Panel->setFillColor(sf::Color(255, 255, 255, 255));
	Panel->setOutlineColor(sf::Color(180, 180, 180, 255));
	Panel->setPosition(pos);

	_Text = new sf::Text("Score : 0", *RessourceManager::getInstance()->getFont(RessourceManager::MLFont));
	_Text->setCharacterSize(24);
	_Text->setFillColor(sf::Color(180,60,60,255));
	_Text->setPosition(pos + sf::Vector2f(30, 20));
}

void ScorePanel::updateScore(int score)
{
	std::string str = "Score : " + std::to_string(score);
	_Text->setString(str);
}

void ScorePanel::draw() const
{
	GameManager::getInstance()->getWindow()->draw(*Panel);
	GameManager::getInstance()->getWindow()->draw(*_Text);
}
