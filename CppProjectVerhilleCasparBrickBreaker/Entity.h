#pragma once
#include <SFML/Graphics.hpp>
#include "GameManager.h"

class Entity
{
public:
	enum class Side{ TOP, BOTTOM, LEFT, RIGHT };
	
protected:
	sf::Vector2f Position;

public:
	Entity() { Position = sf::Vector2f(0, 0); };
	Entity(sf::Vector2f pos);

	sf::Vector2f getPosition() const { return Position; }
	virtual sf::FloatRect getGlobalBounds() const = 0;

	virtual void setPosition(sf::Vector2f pos) { Position = pos; }

	virtual void update(float) { };
	virtual void draw() const { }
};

