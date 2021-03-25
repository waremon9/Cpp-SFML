#pragma once
#include "ShapeEntity.h"

//Border is not a line to reduce risk of ball passing through due to lag
class GameBorder : public ShapeEntity
{

public:
	GameBorder(sf::Vector2f, sf::Vector2f); //position, size
};

