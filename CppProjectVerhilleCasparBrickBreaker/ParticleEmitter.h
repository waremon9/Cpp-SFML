#pragma once
#include "Entity.h"
#include "Particle.h"
#include "ParticleSimple.h"
#include "ParticleComplex.h"

class ParticleEmitter : public Entity
{
private:
	Particle* BaseParticle = nullptr;

	float BaseCooldown; //time between burst
	float Cooldown;
	int QteParticle; //particle each burst
	float EmitterLifeTime;
	sf::Vector2f ParticleLifeTime;
	sf::Vector2f ParticleSpeed;
	sf::Vector2f SpawningAngle;
	sf::Color ParticleColor;

	void resetCooldown();
	void spawnParticle();

public:
	ParticleEmitter(sf::Vector2f position, Particle* particle, float lifetime, float cooldown, int qteParticle, sf::Vector2f particleLifeTime, sf::Vector2f particlespeed, sf::Vector2f spawningAngle, sf::Color particleColor);

	float getEmitterLifeTime() { return EmitterLifeTime; }

	void update(float) override;

	sf::FloatRect getGlobalBounds() const override { return sf::FloatRect(); }//gnéeh
};

