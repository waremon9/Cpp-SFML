#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

class Ball;
class Brick;
class GameBorder;
class NomMarrantTableauUneDimension;
class Particle;
class ParticleEmitter;

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
	std::vector<GameBorder*> AllBorders;
	NomMarrantTableauUneDimension* BricksTableau;
	std::vector<Particle*> AllParticles;
	std::vector<ParticleEmitter*> AllParticleEmitters;
	Canon* _Canon;

	void updateDeltaTime();
	void processEvent();
	void updateEntity();
	void deleteElement();
	void updateScreen();

public:
	static GameManager* getInstance() {
		if (Instance == nullptr) Instance = new GameManager();
		return Instance;
	};

	void loop();

	sf::RenderWindow* getWindow() { return Window; }
};

