#include "Brick.h"

Brick::Brick(sf::Vector2f position, sf::Vector2i coord) : ShapeEntity(position)
{
	Life = 1;
	Score = 100;

	Coordinate = coord;

	//Brick shape/color
	_Shape = new sf::RectangleShape{ sf::Vector2f(90,40) };
	_Shape->setPosition(Position);
	_Shape->setOutlineThickness(-5);

	OutlineColor = sf::Color(160, 160, 160);
	_Shape->setOutlineColor(OutlineColor);
}
