#include "ParticleComplex.h"

ParticleComplex::ParticleComplex(sf::Sprite* sprite)
{
	_Particle = sprite;
}

ParticleComplex::ParticleComplex(float speed, float lifetime, sf::Vector2f dir, sf::Color col, sf::Sprite* sprite) : Particle(speed, lifetime, dir, col)
{
	_Particle = sprite;
	_Particle->setColor(_Color);
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
	return new ParticleComplex(Velocity, LifeTime, Direction, _Color, new sf::Sprite(*_Particle));
}
