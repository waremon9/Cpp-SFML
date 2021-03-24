#pragma once
#include <SFML/Graphics.hpp>
#include "Global.h"
#include "Function.h"
#include "Entity.h"

class Brick;

class Ball : public Entity
{
private:
	
	float Velocity;
	sf::Vector2<float> Direction;
	float Radius = 18;

	std::vector<Entity*> CollisionVector;

public:
	Ball(float, sf::Vector2<float>, float); //speed, position, launchAngle

	sf::Vector2<float> getDirection() const { return Direction; }
	float getVelocity() const { return Velocity; }
	float getRadius() const { return Radius; }
	std::vector<Entity*> getCollisionVector() const { return CollisionVector; }

	void setDirection(sf::Vector2<float> d) { Direction = d; }
	void setVelocity(float v) { Velocity = v; }

	void addInCollisionVector(Entity* e) { CollisionVector.push_back(e); }
	void clearInCollisionVector() { CollisionVector.clear(); }
	void inverseDirectionX() { Direction.x *= -1; }
	void inverseDirectionY() { Direction.y *= -1; }
	void Bounce(sf::Vector2<float>);
	void Move();
};

