#pragma once
#include <SFML/Graphics.hpp>
#include "Global.h"

class Entity
{
public:
	enum class Side{ TOP, BOTTOM, LEFT, RIGHT };
	
protected:
	sf::Vector2<float> Position;
	sf::Shape* _Shape = nullptr;

public:
	Entity() {};
	Entity(sf::Vector2f pos);

	sf::Vector2<float> getPosition() const { return Position; }
	sf::Shape* getShape() const { return _Shape;}

	void setPosition(sf::Vector2f pos) { Position = pos; }

	virtual void update(float) {};
	virtual void draw() const { window.draw(*_Shape); }
};

