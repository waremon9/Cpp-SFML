#pragma once
#include "Particle.h"

class ParticleSimple : public Particle
{
private:
	sf::CircleShape* _Particle = nullptr;

public:
	ParticleSimple(sf::CircleShape*); // shape
	ParticleSimple(float, float, sf::Vector2f, sf::Color, sf::CircleShape*); // speed, lifetime, direction, shape

	sf::Shape* getParticleShape() { return _Particle; }

	void setParticleShape(sf::CircleShape* s) { _Particle = s; }
	void setColor(sf::Color col) override { _Color = col, _Particle->setFillColor(col); }
	void setPosition(sf::Vector2f pos) override { Particle::setPosition(pos); _Particle->setPosition(pos); }

	void update(float) override;
	void draw() const override;
	ParticleSimple* clone() override;

	sf::FloatRect getGlobalBounds() const override { return sf::FloatRect(); }//gnéeh
};

