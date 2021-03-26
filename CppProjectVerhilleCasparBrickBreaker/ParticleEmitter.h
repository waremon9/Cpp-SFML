#pragma once
#include "Entity.h"
#include "Particle.h"

class ParticleEmitter : public Entity
{
private:
	float BaseCooldown; //time between burst
	float Cooldown;
	int QteParticle; //particle each burst
	float EmitterLifeTime;

	void resetCooldown();
	void spawnParticle();

public:
	ParticleEmitter(sf::Vector2f);//position, particle to spawn

	float getEmitterLifeTime() { return EmitterLifeTime; }

	void update(float) override;

	sf::FloatRect getGlobalBounds() const override { return sf::FloatRect(); }//gnéeh
};

