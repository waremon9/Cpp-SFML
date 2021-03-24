#include "GameBorder.h"

GameBorder::GameBorder(sf::Vector2f pos, sf::Vector2f size) : Entity(pos)
{
	Position = pos;
	_Shape = new sf::RectangleShape{ size };
	_Shape->setPosition(Position);
}
