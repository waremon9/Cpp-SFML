#pragma once
#include <SFML/Graphics.hpp>
#include "Entity.h"
#include "Brick.h"
#include "LifeBrick.h"
#include "Ball.h"
#include "GameBorder.h"
#include "Particle.h"
#include "ParticleEmitter.h"

class Ball;

int RandomInt(int, int);
float RandomFloat(float, float);
float convertToRadian(float);
sf::Vector2<float> normalizeVector(sf::Vector2<float>);
sf::Vector2<float> getNormalVector(sf::Vector2<float>, sf::Vector2<float>);
float dotProduct(sf::Vector2<float>, sf::Vector2<float>);
float distance2Points(sf::Vector2<float>, sf::Vector2<float>);
bool vectorContain(const std::vector<Entity*>& , Entity*);
bool intersects(const Entity*, const Entity*);
Entity::Side whichSide(const Entity*, const Entity*);
bool ballIntersects(const Entity*, const Entity*);
void CheckCollisions();
void removeOutOfBoundBall();
void removeDeadBlock();
void removeParticle();
void removeParticleEmitter();