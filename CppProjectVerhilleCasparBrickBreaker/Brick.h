#pragma once
#include <SFML/Graphics.hpp>
#include "ShapeEntity.h"

class Brick : public ShapeEntity
{
protected:
	int Life;
	sf::Vector2i Coordinate;

	sf::Color FillColor;
	sf::Color OutlineColor;

public:
	Brick(sf::Vector2f, sf::Vector2i); //position, coordinate in brick tableau

	int getLife() const { return Life; }
	sf::Vector2i getCoordinate() const { return Coordinate; }

	virtual void damage() { Life--; }
};