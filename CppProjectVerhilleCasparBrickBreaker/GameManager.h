#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>

class Ball;
class Brick;
class GameBorder;
class NomMarrantTableauUneDimension;
class Particle;
class ParticleEmitter;
class Canon;

class GameManager
{
private:
	static GameManager* Instance;
	GameManager();


	sf::RenderWindow* Window;
	sf::Clock* DeltaClock;
	float DeltaTime;
	std::vector<Ball*> AllBalls;
	std::vector<Brick*> AllBricks;
	NomMarrantTableauUneDimension* BricksTableau;
	std::vector<GameBorder*> AllBorders;
	std::vector<Particle*> AllParticles;
	std::vector<ParticleEmitter*> AllParticleEmitters;
	Canon* _Canon;

	void updateDeltaTime();
	void processEvent();
	void updateEntity();
	void deleteElement();
	void updateScreen();

	void initialize();

public:
	static GameManager* getInstance();

	void gameLoop();

	sf::RenderWindow* getWindow() const { return Window; }
	std::vector<Ball*>& getAllBalls() { return AllBalls; }
	std::vector<Brick*>& getAllBricks() { return AllBricks; }
	std::vector<GameBorder*>& getAllBorders() { return AllBorders; }
	std::vector<ParticleEmitter*>& getAllParticleEmitters() { return AllParticleEmitters; }
	std::vector<Particle*>& getAllParticles() { return AllParticles; }
	NomMarrantTableauUneDimension* getBricksTableau() { return BricksTableau; }
};

