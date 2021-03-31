#define _USE_MATH_DEFINES
#pragma once
#include <SFML/Audio.hpp>
#include "SpriteEntity.h"
#include "ParticleComplex.h"

class Canon : public SpriteEntity
{
private:
	float Angle;
	sf::Vector2f Direction;
	sf::Vector2f Origin;
	float BaseCooldown;
	float Cooldown;
	float BallSpeed;

	ParticleComplex* ShootParticle = nullptr;

	void ResetCooldown() { Cooldown = BaseCooldown; }

public:
	Canon();

	void setRotation(float angle);

	void shoot();

	void update(float) override;
};

