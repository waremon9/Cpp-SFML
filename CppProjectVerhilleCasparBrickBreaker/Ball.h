#pragma once
#include <SFML/Audio.hpp>
#include "Global.h"
#include "Function.h"
#include "SpriteEntity.h"

class Brick;

class Ball : public SpriteEntity
{
private:
	
	float Velocity;
	sf::Vector2<float> Direction;
	float Radius = 18;

	std::vector<Entity*> CollisionVector;

	sf::SoundBuffer* Buffer = nullptr;
	sf::Sound* HitSound = nullptr;

public:
	Ball(float, sf::Vector2f, float); //speed, position, launchAngle

	sf::Vector2f getDirection() const { return Direction; }
	float getVelocity() const { return Velocity; }
	float getRadius() const { return Radius; }
	std::vector<Entity*> getCollisionVector() const { return CollisionVector; }

	void setDirection(sf::Vector2f d) { Direction = d; }
	void setVelocity(float v) { Velocity = v; }

	void addInCollisionVector(Entity* e) { CollisionVector.push_back(e); }
	void clearInCollisionVector() { CollisionVector.clear(); }
	void inverseDirectionX() { Direction.x *= -1; }
	void inverseDirectionY() { Direction.y *= -1; }
	void playHitSound() { HitSound->play(); }
	void Bounce(sf::Vector2f);
	void Move();
};

