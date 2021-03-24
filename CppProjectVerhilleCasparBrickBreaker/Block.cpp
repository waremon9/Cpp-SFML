#include "Block.h"

Block::Block(sf::Vector2<float> position) : Entity(position)
{
	_Shape = new sf::RectangleShape{ sf::Vector2f(90,40) };
	_Shape->setPosition(Position);
}