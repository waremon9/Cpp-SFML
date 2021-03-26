#pragma once
#include <SFML/Graphics.hpp>

class Ball;
class Brick;
class Particle;
class ParticleEmitter;

extern sf::RenderWindow window;
extern float deltaTime;
extern std::vector<Ball*> AllBalls;
extern std::vector<Brick*> AllBricks;
extern std::vector<Particle*> AllParticles;
extern std::vector<ParticleEmitter*> AllParticleEmitters;