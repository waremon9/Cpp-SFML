#include "LifeBrick.h"
#include "Global.h"
#include <iostream>

class Brick;
class Entity;

LifeBrick::LifeBrick(sf::Vector2f pos, int life, sf::Font* font) : Brick(pos)
{
	Life = life;
	_Shape->setFillColor(sf::Color(255,60,60));
	_Shape->setOutlineColor(sf::Color(255,180,180));

	TextNumber->setFont(*font);
	UpdateTextNumber();
}

void LifeBrick::UpdateTextNumber()
{
	TextNumber->setString(std::to_string(Life));

	sf::FloatRect textBound = TextNumber->getGlobalBounds();
	sf::Vector2f textSize = sf::Vector2f(textBound.width, textBound.height);

	TextNumber->setPosition(Position + ((sf::RectangleShape*)_Shape)->getSize() / 2.f - textSize / 2.f);
}

void LifeBrick::draw() const {
	Entity::draw();
	window.draw(*TextNumber);
}

void LifeBrick::damage()
{
	Brick::damage();
	UpdateTextNumber();
}
