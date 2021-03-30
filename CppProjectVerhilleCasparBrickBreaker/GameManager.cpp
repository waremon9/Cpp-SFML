#include "GameManager.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <list>
#include "Function.h"
#include "Ball.h"
#include "Brick.h"
#include "LifeBrick.h"
#include "RegenBrick.h"
#include "ExplosiveBrick.h"
#include "Canon.h"
#include "GameBorder.h"
#include "Particle.h"
#include "ParticleSimple.h"
#include "ParticleComplex.h"
#include "ParticleEmitter.h"
#include "NomMarrantTableauUneDimension.h"

GameManager* GameManager::Instance = nullptr;

GameManager::GameManager() {

    
}

void GameManager::gameLoop() {
    //game loop
    while (Window->isOpen())
    {
        updateDeltaTime();

        processEvent();

        updateEntity();

        deleteElement();

        CheckCollisions();

        updateScreen();
    }
}

void GameManager::updateDeltaTime()
{
    DeltaTime = DeltaClock->getElapsedTime().asSeconds();
    DeltaClock->restart();
}

void GameManager::processEvent()
{
    //Process event
    sf::Event event;
    while (Window->pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            Window->close();

        if (event.type == sf::Event::MouseMoved) {
            sf::Vector2f vect((sf::Vector2f)sf::Mouse::getPosition(*Window) - _Canon->getPosition());
            _Canon->setRotation(atan2(vect.y, vect.x));
        }

        if (event.type == sf::Event::MouseButtonPressed)
        {
            if (event.mouseButton.button == sf::Mouse::Left)
            {
                _Canon->shoot();
            }
        }
    }
}

void GameManager::updateEntity()
{
    for (Particle* p : AllParticles) {
        p->update(DeltaTime);
    }

    for (ParticleEmitter* pe : AllParticleEmitters) {
        pe->update(DeltaTime);
    }

    for (Brick* b : AllBricks) {
        b->update(DeltaTime);
    }

    for (Ball* b : AllBalls)
    {
        b->update(DeltaTime);
    }

    _Canon->update(DeltaTime);

}

void GameManager::deleteElement()
{
    removeOutOfBoundBall();
    removeDeadBlock();
    removeParticle();
    removeParticleEmitter();
}

void GameManager::updateScreen()
{
    // Clear screen
    Window->clear();
    //draw everything
    for (Particle* p : AllParticles) {
        if (!p->isFrontParticle()) p->draw();
    }

    for (Ball* b : AllBalls) {
        b->draw();
    }
    for (Brick* b : AllBricks) {
        b->draw();
    }

    _Canon->draw();

    for (Particle* p : AllParticles) {
        if (p->isFrontParticle()) p->draw();
    }

    // Update the window
    Window->display();
}

GameManager* GameManager::getInstance()
{
	if (Instance == nullptr) {
		Instance = new GameManager();
        Instance->initialize();
	}
	return Instance;
}

void GameManager::initialize() {
	srand((unsigned)time(NULL));

	Window = new sf::RenderWindow(sf::VideoMode(1050, 700), "HelloWorld");
	BricksTableau = new NomMarrantTableauUneDimension(10, 5);
	DeltaClock = new sf::Clock;
	DeltaTime = 0;
	_Canon = new Canon();

	sf::Listener::setGlobalVolume(50); // global sound volume

	if (sf::Listener::getGlobalVolume() != 0) {
		sf::SoundBuffer* MusicBuffer = new sf::SoundBuffer;
		MusicBuffer->loadFromFile("Neo Nomen - RERUN OST.wav");
		sf::Sound* Music = new sf::Sound();
		Music->setBuffer(*MusicBuffer);
		Music->play();
		Music->setVolume(40);
	}

	sf::Font* MLFont = new sf::Font;
	MLFont->loadFromFile("MarioLuigi2.ttf");

	float BorderThickness = 10;
	//Borders
	AllBorders.push_back(new GameBorder(sf::Vector2f(0, -BorderThickness), sf::Vector2f(Window->getSize().x, BorderThickness)));//top
	AllBorders.push_back(new GameBorder(sf::Vector2f(-BorderThickness, 0), sf::Vector2f(BorderThickness, Window->getSize().y)));//left
	AllBorders.push_back(new GameBorder(sf::Vector2f(Window->getSize().x, 0), sf::Vector2f(BorderThickness, Window->getSize().y)));//right

	//bricks
	for (int y = 0; y < 5; y++) {
		for (int x = 0; x < 10; x++) {
			Brick* b;
			switch (RandomInt(0, 3) % 4)
			{
			case 0:
				b = new Brick(sf::Vector2f{ 25 + x * 100.f, 20 + y * 50.f }, sf::Vector2i(x, y));
				break;
			case 1:
				b = new LifeBrick(sf::Vector2f{ 25 + x * 100.f, 20 + y * 50.f }, sf::Vector2i(x, y), RandomInt(3, 5), MLFont);
				break;
			case 2:
				b = new RegenBrick(sf::Vector2f{ 25 + x * 100.f, 20 + y * 50.f }, sf::Vector2i(x, y), RandomInt(2, 3), MLFont);
				break;
			case 3:
				b = new ExplosiveBrick(sf::Vector2f{ 25 + x * 100.f, 20 + y * 50.f }, sf::Vector2i(x, y));
				break;
			default:
				break;
			}
			AllBricks.push_back(b);
			BricksTableau->pushBack(b);
		}
	}

	//Particle test
	AllParticleEmitters.push_back(//add the emitter to the list
		new ParticleEmitter(//create emitter
			(sf::Vector2f)Window->getSize() / 2.f,//Position pf emitter, particle position when spawn
			new ParticleSimple(//Particle to spawn
				new sf::CircleShape(3, 10),//Shape of particle , or sprite if ParticleComplex
				0, // Gravity strength
				false //is the particle on front of all or behind
			),
			INFINITY,//emitter LifeTime
			0.05,//Cooldown between burst
			1,//Particle each burst
			sf::Vector2f(3, 3),//Particle LifeTime, random between 2 value
			sf::Vector2f(400, 600),//Particle Speed, random between 2 value
			sf::Vector2f(0, 360),//Particle starting direction, degree, random between 2 value
			sf::Color(180, 180, 180, 200)//Color of the particle
		)
	);
}