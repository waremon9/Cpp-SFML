#include <iostream>
#include <SFML/Graphics.hpp>
#include "Global.h"
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

//global
sf::RenderWindow window(sf::VideoMode(1050,700), "HelloWorld");
float deltaTime;

std::vector<Ball*> AllBalls;
std::vector<Brick*> AllBricks;
std::vector<GameBorder*> AllBorders;
std::vector<Particle*> AllParticles;
std::vector<ParticleEmitter*> AllParticleEmitters;

int main()
{
    srand((unsigned)time(NULL));

    sf::Clock deltaClock;

    sf::Font* MLFont = new sf::Font;
    MLFont->loadFromFile("MarioLuigi2.ttf");

    float BorderThickness = 10;
    //Borders
    AllBorders.push_back(new GameBorder(sf::Vector2f(0, -BorderThickness), sf::Vector2f(window.getSize().x, BorderThickness)));//top
    AllBorders.push_back(new GameBorder(sf::Vector2f(-BorderThickness, 0), sf::Vector2f(BorderThickness, window.getSize().y)));//left
    AllBorders.push_back(new GameBorder(sf::Vector2f(window.getSize().x, 0), sf::Vector2f(BorderThickness, window.getSize().y)));//right

    //bricks
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 5; j++) {
            switch (RandomInt(0,3) % 4)
            {
            case 0:
                AllBricks.push_back(new Brick(sf::Vector2f{ 25 + i * 100.f, 20 + j * 50.f }));
                break;
            case 1:
                AllBricks.push_back(new LifeBrick(sf::Vector2f{ 25 + i * 100.f, 20 + j * 50.f }, RandomInt(3, 5), MLFont));
                break;
            case 2:
                AllBricks.push_back(new RegenBrick(sf::Vector2f{ 25 + i * 100.f, 20 + j * 50.f }, RandomInt(2, 3), MLFont));
                break;
            case 3:
                AllBricks.push_back(new ExplosiveBrick(sf::Vector2f{ 25 + i * 100.f, 20 + j * 50.f }));
                break;
            default:
                break;
            }
        }
    }

    //Canon
    Canon* canon = new Canon();

    //Particle test
    AllParticleEmitters.push_back(new ParticleEmitter(sf::Vector2f(500,400),
        new ParticleSimple(sf::Vector2f(500,400), new sf::CircleShape(2,10) ),
        15, 0.02, 20
        ));

    //game loop
    while (window.isOpen())
    {
        deltaTime = deltaClock.getElapsedTime().asSeconds();
        deltaClock.restart();

        //Process event
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseMoved) {
                sf::Vector2f vect((sf::Vector2f)sf::Mouse::getPosition(window) - canon->getPosition());
                canon->setRotation(atan2(vect.y, vect.x));
            }

            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    canon->shoot();
                }
            }
        }

        for (Particle* p : AllParticles) {
            p->update(deltaTime);
        }

        for (ParticleEmitter* pe : AllParticleEmitters) {
            pe->update(deltaTime);
        }

        for (Brick* b : AllBricks) {
            b->update(deltaTime);
        }

        canon->update(deltaTime);

        for (Ball* b : AllBalls) 
        {
            b->Move();
        }

        removeOuOfBoundBall();
        removeDeadBlock();
        removeParticle();
        removeParticleEmitter();

        CheckCollisions(AllBricks, AllBalls, AllBorders);


        // Clear screen
        window.clear();
        //draw everything
        for (Ball* b : AllBalls) {
            b->draw();
        }
        for (Brick* b : AllBricks) {
            b->draw();
        }

        canon->draw();

        for (Particle* p : AllParticles) {
            p->draw();
        }

        // Update the window
        window.display();
    }

    return 0;
}