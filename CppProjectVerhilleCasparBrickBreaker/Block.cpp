#include "Block.h"

Block::Block(sf::Vector2<float> position)
{
	Position = position;
	Square->setPosition(Position);
}
