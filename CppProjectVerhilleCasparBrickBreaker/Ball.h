#pragma once
#include <SFML/Graphics.hpp>
#include "Global.h"
#include "Function.h"
#include "Entity.h"

class Block;

class Ball : public Entity
{
private:
	
	float Velocity;
	sf::Vector2<float> Direction;
	float Radius = 20;

	std::vector<Entity*> CollisionVector;

	bool intersects(const Entity*) const;
	void whichSide(const Entity*);
	bool ballIntersects(const Entity*) const;

public:
	Ball(float, sf::Vector2<float>, float); //speed, position, launchAngle

	sf::Vector2<float> getDirection() { return Direction; }
	float getVelocity() { return Velocity; }
	float getRadius() { return Radius; }

	void setDirection(sf::Vector2<float> d) { Direction = d; }
	void setVelocity(float v) { Velocity = v; }

	void Bounce(sf::Vector2<float>);
	void Move();
	void CheckCollisions(std::vector<Block*>, std::vector<Ball*>);
};

