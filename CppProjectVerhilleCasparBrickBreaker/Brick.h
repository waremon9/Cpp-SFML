#pragma once
#include <SFML/Graphics.hpp>
#include "Global.h"
#include "ShapeEntity.h"

class Brick : public ShapeEntity
{
protected:
	int Life;

	sf::Color FillColor;
	sf::Color OutlineColor;

public:
	Brick(sf::Vector2<float>); //position

	int getLife() const { return Life; }

	virtual void damage() { Life--; }
};