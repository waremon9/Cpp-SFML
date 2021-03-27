#include "Particle.h"

Particle::Particle(sf::Vector2f pos) : Entity(pos)
{
	Velocity = 0;
	LifeTime = 0;
	Direction = sf::Vector2f(0,0);
}

Particle::Particle(sf::Vector2f pos, float velo, float life, sf::Vector2f dir) : Entity(pos)
{
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
}

