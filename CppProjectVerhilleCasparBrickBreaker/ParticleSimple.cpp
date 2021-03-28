#include "ParticleSimple.h"
#include <iostream>

#include "Function.h"

ParticleSimple::ParticleSimple(sf::CircleShape* shape, float gra, bool b)
{
	_Particle = shape;
	GravityStrenght = gra;
	IsFrontParticle = b;
}

ParticleSimple::ParticleSimple(float speed, float lifetime, sf::Vector2f dir, float gra, sf::Color col, sf::CircleShape* shape, bool front) : Particle(speed, lifetime, dir, gra, col, front)
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
	return new ParticleSimple(Velocity, LifeTime, Direction, GravityStrenght, _Color, new sf::CircleShape(*_Particle), IsFrontParticle);
}
