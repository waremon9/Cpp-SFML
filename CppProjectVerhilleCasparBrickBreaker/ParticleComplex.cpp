#include "ParticleComplex.h"

ParticleComplex::ParticleComplex(sf::Sprite* sprite, float gra, bool b)
{
	_Particle = sprite;
	IsFrontParticle = b;
	GravityStrenght = gra;

	_Particle->setOrigin(sf::Vector2f(_Particle->getGlobalBounds().width * _Particle->getScale().x / 2.f, _Particle->getGlobalBounds().height * _Particle->getScale().y / 2.f));
}

ParticleComplex::ParticleComplex(float speed, float lifetime, sf::Vector2f dir, float gra, sf::Color col, sf::Sprite* sprite, bool front) : Particle(speed, lifetime, dir, gra, col, front)
{
	_Particle = sprite;
	_Particle->setColor(_Color);

	_Particle->setOrigin(sf::Vector2f(_Particle->getGlobalBounds().width * _Particle->getScale().x / 2.f, _Particle->getGlobalBounds().height * _Particle->getScale().y / 2.f));
}

void ParticleComplex::update(float dt)
{
	Particle::update(dt);
	_Particle->setPosition(Position);
}

void ParticleComplex::draw() const
{
	GameManager::getInstance()->getWindow()->draw(*_Particle);
}

ParticleComplex* ParticleComplex::clone()
{
	return new ParticleComplex(Velocity, LifeTime, Direction, GravityStrenght, _Color, new sf::Sprite(*_Particle), IsFrontParticle);
}
