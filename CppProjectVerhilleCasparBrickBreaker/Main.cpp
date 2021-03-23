#include <iostream>
#include <SFML/Graphics.hpp>
#include "Global.h"
#include "Function.h"
#include "Ball.h"
#include "Block.h"
#include "Canon.h"

void createBall();

//global
sf::RenderWindow window(sf::VideoMode(1050,700), "HelloWorld");
float deltaTime;

std::vector<Ball*> AllBalls;
std::vector<Block*> AllBricks;

int main()
{
    srand(time(NULL));//make random really random

    sf::Clock deltaClock;

    //ball
    /*
    for (int i = 0; i < 10; i++) {
        createBall();
    }*/

    //bricks
    AllBricks.push_back(new Block(sf::Vector2f{200, 200}));
    AllBricks.push_back(new Block(sf::Vector2f{600, 200}));
    AllBricks.push_back(new Block(sf::Vector2f{500, 400}));

    //Canon
    Canon* canon = new Canon();

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

        for (Ball* b : AllBalls) 
        {
            b->Move();
        }

        CheckCollisions(AllBricks, AllBalls);

        // Clear screen
        window.clear();
        //draw everything
        for (Ball* b : AllBalls) {
            b->draw();
        }
        for (Block* b : AllBricks) {
            b->draw();
        }

        canon->draw();

        // Update the window
        window.display();
    }

    return 0;
}

void createBall() {
    float speed = RandomInt(400,800);
    sf::Vector2<float> pos{ (float)RandomInt(0,window.getSize().x - 40), (float)RandomInt(0,window.getSize().y - 40) };
    float angle = RandomInt(0, 359);
    AllBalls.push_back(new Ball(speed, pos, angle));
}