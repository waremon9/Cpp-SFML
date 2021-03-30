#include "ParticleEmitter.h"
#include "Function.h"
#include <iostream>

#include "Particle.h"
#include "ParticleSimple.h"
#include "ParticleComplex.h"

ParticleEmitter::ParticleEmitter(sf::Vector2f pos, Particle* particle, float lifetime, float cooldown, int qteParticle, sf::Vector2f particleLifeTime, sf::Vector2f particleSpeed, sf::Vector2f spawningAngle, sf::Color particleColor) : Entity(pos)
{
	BaseParticle = particle;
	BaseCooldown = Cooldown = cooldown;
	QteParticle = qteParticle;
	EmitterLifeTime = lifetime;
	ParticleLifeTime = particleLifeTime;
	ParticleSpeed = particleSpeed;
	SpawningAngle = spawningAngle;
	ParticleColor = particleColor;
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
	float RandomLifeTime = RandomFloat(ParticleLifeTime.x, ParticleLifeTime.y);
	partTmp->setLifeTime(RandomLifeTime);
	float RandomSpeed = RandomFloat(ParticleSpeed.x, ParticleSpeed.y);
	partTmp->setVelocity(RandomSpeed);
	float RandomAngle = RandomFloat(SpawningAngle.x, SpawningAngle.y);
	partTmp->setDirection(sf::Vector2f(std::cos(convertToRadian(RandomAngle)), std::sin(convertToRadian(RandomAngle))));
	partTmp->setColor(ParticleColor);

	GameManager::getInstance()->getAllParticles().push_back(partTmp);
}

void ParticleEmitter::resetCooldown()
{
	Cooldown = BaseCooldown;
}
