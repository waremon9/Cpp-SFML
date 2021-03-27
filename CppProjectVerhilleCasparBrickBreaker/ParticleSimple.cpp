#include "ParticleSimple.h"
#include <iostream>

#include "Function.h"

ParticleSimple::ParticleSimple(sf::Vector2f pos, sf::CircleShape* shape) : Particle(pos)
{
	_Particle = shape;
}

ParticleSimple::ParticleSimple(sf::Vector2f pos, float speed, float lifetime, sf::Vector2f dir, sf::CircleShape* shape) : Particle(pos)
{
	Velocity = speed;
	LifeTime = lifetime;
	Direction = dir;
	_Particle = shape;
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
	return new ParticleSimple(Position, Velocity, LifeTime, Direction, new sf::CircleShape(*_Particle));
}
