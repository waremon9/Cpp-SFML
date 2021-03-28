#include "ParticleSimple.h"
#include <iostream>

#include "Function.h"

ParticleSimple::ParticleSimple(sf::CircleShape* shape)
{
	_Particle = shape;
}

ParticleSimple::ParticleSimple(float speed, float lifetime, sf::Vector2f dir, sf::Color col, sf::CircleShape* shape) : Particle(speed, lifetime, dir, col)
{
	_Particle = shape;
	_Particle->setFillColor(_Color);
}

void ParticleSimple::update(float dt)
{
	Particle::update(dt);
	_Particle->setPosition(Position);
}

void ParticleSimple::draw() const
{
	Particle::draw();
	window.draw(*_Particle);
}

ParticleSimple* ParticleSimple::clone()
{
	return new ParticleSimple(Velocity, LifeTime, Direction, _Color, new sf::CircleShape(*_Particle));
}
