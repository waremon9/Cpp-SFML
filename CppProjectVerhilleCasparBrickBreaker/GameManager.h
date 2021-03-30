#pragma once
#include <SFML/Graphics.hpp>

class Ball;
class Brick;
class Particle;
class ParticleEmitter;
class NomMarrantTableauUneDimension;

class GameManager
{
private:
	static GameManager* Instance;
	GameManager();


	sf::RenderWindow* window;
	float deltaTime;
	std::vector<Ball*> AllBalls;
	std::vector<Brick*> AllBricks;
	NomMarrantTableauUneDimension* BricksTableau;
	std::vector<Particle*> AllParticles;
	std::vector<ParticleEmitter*> AllParticleEmitters;

public:
	static GameManager* getInstance() {
		if (Instance == nullptr) Instance = new GameManager();
		return Instance;
	};

	sf::RenderWindow* getWindow() { return window; }
	float getDeltaTime() { return deltaTime; }
	std::vector<Ball*> getAllBalls() { return AllBalls; }
	std::vector<Brick*> getAllBricks() { return AllBricks; }
	NomMarrantTableauUneDimension* getBricksTableau() { return BricksTableau; }
	std::vector<Particle*> getAllParticles() { return AllParticles; }
	std::vector<ParticleEmitter*> getAllParticleEmitters() { return AllParticleEmitters; }

};

