#pragma once
#include "Particle.h"
class ParticleComplex : public Particle
{
private:
	sf::Sprite* _Particle = nullptr;

public:
	ParticleComplex(sf::Sprite*); // shape
	ParticleComplex(float, float, sf::Vector2f, sf::Color, sf::Sprite*); // speed, lifetime, direction, shape

	sf::Sprite* getParticleSprite() { return _Particle; }

	void setParticleSprite(sf::Sprite* s) { _Particle = s; }
	void setColor(sf::Color col) override { _Color = col, _Particle->setColor(col); }
	void setPosition(sf::Vector2f pos) override { Particle::setPosition(pos); _Particle->setPosition(pos); }

	void update(float) override;
	void draw() const override;
	ParticleComplex* clone() override;
};

