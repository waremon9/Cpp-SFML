#pragma once
#include <SFML/Graphics.hpp>
#include "Global.h"
#include "Entity.h"

class Brick : public Entity
{
protected:
	int Life = 1;

public:
	Brick(sf::Vector2<float>); //position

	int getLife() const { return Life; }

	void damage() { Life--; }
};

