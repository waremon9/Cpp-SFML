#define _USE_MATH_DEFINES
#pragma once
#include "Entity.h"

class Canon : public Entity
{
private:
	float Angle;
	sf::Vector2f Direction;
	sf::Vector2f Origin;
	float BaseCooldown;
	float Cooldown;
	float BallSpeed;

	void ResetCooldown() { Cooldown = BaseCooldown; }

public:
	Canon();

	void setRotation(float angle);

	void shoot();

	void update(float) override;
};

