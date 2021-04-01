#pragma once
#include "Brick.h"
#include "ParticleComplex.h"
#include <SFML/Audio.hpp>

class ExplosiveBrick : public Brick
{
private:
	bool AlreadyExplode;

	sf::Sprite* BombIcon;

	ParticleComplex* ExplosionParticle = nullptr;

	void explode();

public:
	ExplosiveBrick(sf::Vector2f, sf::Vector2i); //position

	void damage() override;
	void draw() const override;
};