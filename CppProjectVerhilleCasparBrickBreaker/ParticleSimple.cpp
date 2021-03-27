#include "ParticleSimple.h"
#include <iostream>

#include "Function.h"

ParticleSimple::ParticleSimple(sf::CircleShape* shape)
{
	_Particle = shape;
	_Particle->setPosition(Position);
}

ParticleSimple::ParticleSimple(float speed, float lifetime, sf::Vector2f dir, sf::CircleShape* shape)
{
	Velocity = speed;
	LifeTime = lifetime;
	Direction = dir;
	_Particle = shape;
	_Particle->setPosition(Position);
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
	return new ParticleSimple(Velocity, LifeTime, Direction, new sf::CircleShape(*_Particle));
}
