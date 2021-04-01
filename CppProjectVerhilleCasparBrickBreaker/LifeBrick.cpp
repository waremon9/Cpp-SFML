#include "LifeBrick.h"
#include <iostream>
#include "UIManager.h"
#include "GameManager.h"

class Brick;
class Entity;

LifeBrick::LifeBrick(sf::Vector2f pos, sf::Vector2i coord, int life, sf::Font* font) : Brick(pos, coord)
{
	Life = life;
	HitScore = 20;

	//Brick color
	FillColor = sf::Color(255, 60, 60);
	OutlineColor = sf::Color(255, 180, 180);

	_Shape->setFillColor(FillColor);
	_Shape->setOutlineColor(OutlineColor);

	//brick text number
	TextNumber->setFont(*font);
	UpdateTextNumber();
}

int LifeBrick::getHitScore()
{
	return HitScore;
}

void LifeBrick::UpdateTextNumber()
{
	TextNumber->setString(std::to_string(Life));

	sf::FloatRect textBound = TextNumber->getGlobalBounds();
	sf::Vector2f textSize = sf::Vector2f(textBound.width, textBound.height);

	TextNumber->setPosition(Position + ((sf::RectangleShape*)_Shape)->getSize() / 2.f - textSize / 2.f);
}

void LifeBrick::draw() const {
	Brick::draw();
	GameManager::getInstance()->getWindow()->draw(*TextNumber);
}

void LifeBrick::damage()
{
	Brick::damage();
	UpdateTextNumber();
	UIManager::getInstance()->addScore(getHitScore());//getpoint when ball hit
}
