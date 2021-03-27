#include "ParticleComplex.h"

ParticleComplex::ParticleComplex(sf::Vector2f pos, sf::Sprite* sprite) : Particle(pos)
{
	_Particle = sprite;
}

ParticleComplex::ParticleComplex(sf::Vector2f pos, float speed, float lifetime, sf::Vector2f dir, sf::Sprite* sprite) : Particle(pos)
{
	_Particle = sprite;
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
	return new ParticleComplex(Position, Velocity, LifeTime, Direction, new sf::Sprite(*_Particle));
}
