#pragma once
#include "Entity.h"
#include <iostream>

class Particle : public Entity
{
protected:
	float LifeTime; // amount of time the particle is active (in second)
	float Velocity; // speed of the particle
	sf::Vector2f Direction; // direction of the particle, normalize vector
	sf::Color _Color; // color of the particle
	float GravityStrenght;

	bool IsFrontParticle; // is the particle on top of everything or behind everything

	void move(float);

public:
	Particle();
	Particle(float, float, sf::Vector2f, float, sf::Color, bool); // speed, lifetime, direction, gravity, color, front/back

	void setDirection(sf::Vector2f dir) { Direction = dir; }
	void setVelocity(float vel) { Velocity = vel; }
	void setLifeTime(float lt) { LifeTime = lt; }
	virtual void setColor(sf::Color c) = 0;
	void setIsFrontPartice(bool b) { IsFrontParticle = b; }

	sf::Vector2f getDirection() const { return Direction; }
	float getVelocity() const { return Velocity; }
	float getLifeTime() const { return LifeTime; }
	bool isFrontParticle() const { return IsFrontParticle; }

	virtual void update(float) override;

	virtual Particle* clone() = 0; //return a clone of the original

	virtual sf::FloatRect getGlobalBounds() const override = 0;
};

