#include "ParticleComplex.h"

ParticleComplex::ParticleComplex(sf::Sprite* sprite)
{
	_Particle = sprite;
	_Particle->setPosition(Position);
}

ParticleComplex::ParticleComplex(float speed, float lifetime, sf::Vector2f dir, sf::Sprite* sprite)
{
	_Particle = sprite;
	_Particle->setPosition(Position);
}

void ParticleComplex::update(float dt)
{
	Particle::update(dt);
	_Particle->setPosition(Position);
}

void ParticleComplex::draw() const
{
	window.draw(*_Particle);
}

ParticleComplex* ParticleComplex::clone()
{
	return new ParticleComplex(Velocity, LifeTime, Direction, new sf::Sprite(*_Particle));
}
