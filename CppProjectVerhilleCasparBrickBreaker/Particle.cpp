#include "Particle.h"

Particle::Particle(sf::Vector2f pos) : Entity(pos)
{
	parti = new sf::CircleShape(1.5);
	parti->setFillColor(sf::Color::Green);
	Velocity = 0;
	LifeTime = 0;
	Direction = sf::Vector2f(0,0);
}

Particle::Particle(sf::Vector2f pos, float velo, float life, sf::Vector2f dir) : Entity(pos)
{
	parti = new sf::CircleShape(3);
	parti->setFillColor(sf::Color::Green);
	Velocity = velo;
	LifeTime = life;
	Direction = dir;
}

void Particle::update(float dt)
{
	LifeTime -= dt;
	move(dt);
}

void Particle::move(float dt) {
	Position += Direction * Velocity * dt;
	parti->setPosition(Position);
}

void Particle::draw() const
{
	window.draw(*parti);
}

Particle* Particle::clone(Particle* p)
{
	return new Particle(p->getPosition(), p->getVelocity(), p->getLifeTime(), p->getDirection());
}
