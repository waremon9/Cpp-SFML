#include <iostream>
#include <SFML/Graphics.hpp>
#include "Global.h"
#include "Function.h"
#include "Ball.h"
#include "Brick.h"
#include "LifeBrick.h"
#include "Canon.h"
#include "GameBorder.h"

void createBall();

//global
sf::RenderWindow window(sf::VideoMode(1050,700), "HelloWorld");
float deltaTime;

std::vector<Ball*> AllBalls;
std::vector<Brick*> AllBricks;
std::vector<GameBorder*> AllBorders;

int main()
{

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
            AllBricks.push_back(new LifeBrick(sf::Vector2f{ 25 + i * 100.f, 20 + j * 50.f }, 3, MLFont));
        }
    }

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

        removeOuOfBoundBall();
        removeDeadBlock();

        CheckCollisions(AllBricks, AllBalls, AllBorders);


        // Clear screen
        window.clear();
        //draw everything
        for (Ball* b : AllBalls) {
            b->draw();
        }
        for (Brick* b : AllBricks) {
            ((LifeBrick*)b)->draw();
        }

        canon->draw();

        for (GameBorder* b : AllBorders) {
            b->draw();
        }
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