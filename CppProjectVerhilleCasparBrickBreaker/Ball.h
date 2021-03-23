#pragma once
#include <SFML/Graphics.hpp>
#include "Global.h"
#include "Function.h"

class Block;

class Ball
{
private:
	sf::CircleShape* Circle = new sf::CircleShape{ 20,20 };
	float Velocity;
	sf::Vector2<float> Direction;
	sf::Vector2<float> Position;

	bool intersects(sf::CircleShape, sf::RectangleShape);
	bool intersects(sf::CircleShape, sf::CircleShape);

public:
	Ball(float, sf::Vector2<float>, float); //speed, position, launchAngle

	sf::CircleShape getShape() { return *Circle; }
	sf::Vector2<float> getPosition() { return Position; }
	sf::Vector2<float> getDirection() { return Direction; }
	float getVelocity() { return Velocity; }

	void setDirection(sf::Vector2<float> d) { Direction = d; }
	void setVelocity(float v) { Velocity = v; }

	void Bounce(sf::Vector2<float>);
	void Move();
	void CheckColisions(std::vector<Block*>, std::vector<Ball*>);

	void draw() { window.draw(*Circle); }
};

