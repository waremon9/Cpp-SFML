#include "ParticleSimple.h"
#include <iostream>

#include "Function.h"

ParticleSimple::ParticleSimple(sf::CircleShape* shape, float gra, bool b)
{
	_Particle = shape;
	GravityStrenght = gra;
	IsFrontParticle = b;

	_Particle->setOrigin(sf::Vector2f(_Particle->getGlobalBounds().width / 2.f, _Particle->getGlobalBounds().height / 2.f));
}

ParticleSimple::ParticleSimple(float speed, float lifetime, sf::Vector2f dir, float gra, sf::Color col, sf::CircleShape* shape, bool front) : Particle(speed, lifetime, dir, gra, col, front)
{
	_Particle = shape;
	_Particle->setFillColor(_Color);

	_Particle->setOrigin(sf::Vector2f(_Particle->getGlobalBounds().width / 2.f, _Particle->getGlobalBounds().height / 2.f));
}

void ParticleSimple::update(float dt)
{
	Particle::update(dt);
	_Particle->setPosition(Position);
}

void ParticleSimple::draw() const
{
	Particle::draw();
	GameManager::getInstance()->getWindow()->draw(*_Particle);
}

ParticleSimple* ParticleSimple::clone()
{
	return new ParticleSimple(Velocity, LifeTime, Direction, GravityStrenght, _Color, new sf::CircleShape(*_Particle), IsFrontParticle);
}
