#include "ParticleEmitter.h"
#include "Function.h"
#include <iostream>

class Particle;

ParticleEmitter::ParticleEmitter(sf::Vector2f pos) : Entity(pos)
{
	BaseCooldown = Cooldown = 0.03;
	QteParticle = 15;
	EmitterLifeTime = 100;
}

void ParticleEmitter::update(float dt)
{
	Cooldown -= dt;
	EmitterLifeTime -= dt;
	if (Cooldown <= 0) {
		resetCooldown();
		for (int i = 0; i < QteParticle; i++) {
			spawnParticle();
		}
	}
}

void ParticleEmitter::spawnParticle() {
	Particle* partTmp = new Particle(Position);
	partTmp->setLifeTime(RandomInt(3,15)/10.f);
	partTmp->setVelocity(RandomInt(50, 150));
	partTmp->setDirection(normalizeVector(sf::Vector2f(RandomInt(-10000, 10000), RandomInt(-10000, 10000))));
	AllParticles.push_back(partTmp);
}

void ParticleEmitter::resetCooldown()
{
	Cooldown = BaseCooldown;
}
