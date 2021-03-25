#include "Explosion.h"

Explosion::Explosion(sf::Vector2f pos, sf::Shape* shape) : ShapeEntity(pos)
{
	_Shape = shape;
	_Shape->setOrigin(sf::Vector2f(_Shape->getGlobalBounds().width / 2, _Shape->getGlobalBounds().height / 2));
	_Shape->setPosition(pos);
}
