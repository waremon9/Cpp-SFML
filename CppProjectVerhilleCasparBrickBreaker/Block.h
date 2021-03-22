#pragma once
#include <SFML/Graphics.hpp>
#include "Global.h"

class Block
{
private:
	sf::RectangleShape* Square = new sf::RectangleShape{ sf::Vector2<float>{90,40} };
	sf::Vector2<float> Position;

public:
	Block(sf::Vector2<float>); //position

	sf::RectangleShape getShape() { return *Square; }
	sf::Vector2<float> getPosition() { return Position; }

	void draw() { window.draw(*Square); }
};

