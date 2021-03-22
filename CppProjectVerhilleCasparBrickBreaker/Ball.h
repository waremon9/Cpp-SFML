#pragma once
#include <SFML/Graphics.hpp>
#include "Global.h"
#include "Function.h"

class Ball
{
private:
	sf::CircleShape Circle{ 20,20 };
	float BaseSpeed;
	sf::Vector2<float> Velocity;
	sf::Vector2<float> Position;

public:
	Ball(float, sf::Vector2<float>, float); //speed, position, launchAngle

	sf::CircleShape getShape() { return Circle; }
	sf::Vector2<float> getPosition() { return Position; }

	void Bounce(sf::Vector2<float>);
	void Move();

	void draw() { window.draw(Circle); }
};

