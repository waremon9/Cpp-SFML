#pragma once
#include <SFML/Graphics.hpp>
#include "Global.h"
#include "Entity.h"

class Brick : public Entity
{
protected:
	int Life = 1;

	sf::Color FillColor;
	sf::Color OutlineColor;

public:
	Brick(sf::Vector2<float>); //position

	int getLife() const { return Life; }

	virtual void damage() { Life--; }
};