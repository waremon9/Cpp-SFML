#include "ParticleEmitter.h"
#include "Function.h"
#include <iostream>

#include "Particle.h"
#include "ParticleSimple.h"
#include "ParticleComplex.h"

ParticleEmitter::ParticleEmitter(sf::Vector2f pos, Particle* particle, float lifetime, float cooldown, int qteParticle) : Entity(pos)
{
	BaseParticle = particle;
	BaseCooldown = Cooldown = cooldown;
	QteParticle = qteParticle;
	EmitterLifeTime = lifetime;
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

	Particle* partTmp = BaseParticle->clone();

	partTmp->setPosition(Position);
	partTmp->setLifeTime(2);
	partTmp->setVelocity(300);
	partTmp->setDirection(normalizeVector(sf::Vector2f(RandomInt(-10000, 10000), RandomInt(-10000, 10000))));

	Particle* part = new ParticleSimple(Position, 300, 2, normalizeVector(sf::Vector2f(RandomInt(-10000, 10000), RandomInt(-10000, 10000))), new sf::CircleShape(3,10));

	AllParticles.push_back(partTmp);
}

void ParticleEmitter::resetCooldown()
{
	Cooldown = BaseCooldown;
}
