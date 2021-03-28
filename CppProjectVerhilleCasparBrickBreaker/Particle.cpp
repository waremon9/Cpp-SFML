#include "Particle.h"

Particle::Particle()
{
	Velocity = 0;
	LifeTime = 0;
	Direction = sf::Vector2f(0,0);
}

Particle::Particle(float velo, float life, sf::Vector2f dir, sf::Color col)
{
	Velocity = velo;
	LifeTime = life;
	Direction = dir;
	_Color = col;
}

void Particle::update(float dt)
{
	LifeTime -= dt;
	move(dt);
}

void Particle::move(float dt) {
	Position += Direction * Velocity * dt;
}

