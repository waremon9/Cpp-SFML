#define _USE_MATH_DEFINES
#pragma once
#include "Entity.h"

class Canon : public Entity
{
private:
	float Angle = 0;
	sf::Vector2f Direction;
	sf::Vector2f Origin;
	float Cooldown = 0.5;
	sf::Clock* clock = new sf::Clock;

public:
	Canon();

	void setRotation(float angle);

	void shoot();
};

