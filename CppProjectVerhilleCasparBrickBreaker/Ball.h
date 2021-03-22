#pragma once
#include <SFML/Graphics.hpp>
#include "Global.h"
#include "Function.h"

class Block;

class Ball
{
private:
	sf::CircleShape* Circle = new sf::CircleShape{ 20,20 };
	float BaseSpeed;
	sf::Vector2<float> Velocity;
	sf::Vector2<float> Position;

	bool intersects(sf::CircleShape, sf::RectangleShape);

public:
	Ball(float, sf::Vector2<float>, float); //speed, position, launchAngle

	sf::CircleShape getShape() { return *Circle; }
	sf::Vector2<float> getPosition() { return Position; }

	void Bounce(sf::Vector2<float>);
	void Move();
	void CheckColisions(std::vector<Block*>);

	void draw() { window.draw(*Circle); }
};

