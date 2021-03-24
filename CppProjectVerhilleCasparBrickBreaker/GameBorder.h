#pragma once
#include "Entity.h"

//Border is not a line to reduce risk of ball passing through due to lag
class GameBorder : public Entity
{

public:
	GameBorder(sf::Vector2f, sf::Vector2f); //position, size
};

