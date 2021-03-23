#pragma once
#include <SFML/Graphics.hpp>
#include "Global.h"

class Entity
{
protected:
	sf::Vector2<float> Position;
	sf::Shape* _Shape;

public:
	Entity(sf::Vector2<float>);
	sf::Vector2<float> getPosition() const { return Position; }
	sf::Shape* getShape() const { return _Shape;}

	void draw() const { window.draw(*_Shape); }
};

