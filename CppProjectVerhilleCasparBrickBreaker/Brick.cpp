#include "Brick.h"

Brick::Brick(sf::Vector2<float> position) : Entity(position)
{
	_Shape = new sf::RectangleShape{ sf::Vector2f(90,40) };
	_Shape->setPosition(Position);
	_Shape->setOutlineThickness(-5);

	OutlineColor = sf::Color(160, 160, 160);
	_Shape->setOutlineColor(OutlineColor);
}
