#pragma once
#include "ShapeEntity.h"
class Explosion : public ShapeEntity
{
public:
	Explosion(sf::Vector2f, sf::Shape*); //postion, explosion hitbox
};

