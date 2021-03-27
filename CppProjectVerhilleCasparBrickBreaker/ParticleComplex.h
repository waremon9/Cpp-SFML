#pragma once
#include "Particle.h"
class ParticleComplex : public Particle
{
private:
	sf::Sprite* _Particle = nullptr;

public:
	ParticleComplex(sf::Vector2f, sf::Sprite*); // position, shape
	ParticleComplex(sf::Vector2f, float, float, sf::Vector2f, sf::Sprite*); // positio,  speed, lifetime, direction, shape

	sf::Sprite* getParticleSprite() { return _Particle; }
	void setParticleSprite(sf::Sprite* s) { _Particle = s; }

	void update(float) override;
	void draw() const override;
	ParticleComplex* clone() override;
};

