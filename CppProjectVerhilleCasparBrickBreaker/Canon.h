#define _USE_MATH_DEFINES
#pragma once
#include "ShapeEntity.h"

class Canon : public ShapeEntity
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

