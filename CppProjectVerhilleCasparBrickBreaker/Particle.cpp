#include "Particle.h"
#include "Function.h"

Particle::Particle()
{
	Velocity = 0;
	LifeTime = 0;
	Direction = sf::Vector2f(0,0);
	IsFrontParticle = false;
	GravityStrenght = 0;
}

Particle::Particle(float velo, float life, sf::Vector2f dir, float gravity, sf::Color col, bool front)
{
	Velocity = velo;
	LifeTime = life;
	Direction = dir;
	_Color = col;
	IsFrontParticle = front;
	GravityStrenght = gravity;
}

void Particle::update(float dt)
{
	LifeTime -= dt;
	move(dt);
}

void Particle::move(float dt) {
	Position += Direction * Velocity * dt;
	if (Direction.y < 1) {//when gravity enable, make the particle fall
		Direction.y += GravityStrenght * dt;
		Direction = normalizeVector(Direction);
	}
}

