#pragma once
#include "Entity.h"

class Particle : public Entity
{
protected:
	//for test
	sf::CircleShape* parti;

	float LifeTime;
	float Velocity;
	sf::Vector2f Direction;

	void move(float);

public:
	Particle(sf::Vector2f); //position
	Particle(sf::Vector2f, float, float, sf::Vector2f); //position, speed, lifetime, direction

	void setDirection(sf::Vector2f dir) { Direction = dir; }
	void setVelocity(float vel) { Velocity = vel; }
	void setLifeTime(float lt) { LifeTime = lt; }

	sf::Vector2f getDirection() const { return Direction; }
	float getVelocity() const { return Velocity; }
	float getLifeTime() const { return LifeTime; }

	void update(float) override;
	void draw() const override;

	Particle* clone(Particle*); //return a clone of the original

	sf::FloatRect getGlobalBounds() const override { return sf::FloatRect(); }//gnéeh
};

