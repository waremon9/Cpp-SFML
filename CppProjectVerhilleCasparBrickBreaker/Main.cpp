#include <iostream>
#include <SFML/Graphics.hpp>
#include "Global.h"
#include "Function.h"
#include "Ball.h"

void createBall();

sf::RenderWindow window(sf::VideoMode(1050,700), "HelloWorld");

std::vector<Ball*> AllBalls;

int main()
{
    srand(time(NULL));//make random really random

    //window
    window.setFramerateLimit(60);

    //ball
    for (int i = 0; i < 10; i++) {
        createBall();
    }

    //game loop
    while (window.isOpen())
    {
        //Process event
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        for (Ball* b : AllBalls) {
            b->Move();
        }

        // Clear screen
        window.clear();
        //draw everything
        for (Ball* b : AllBalls) {
            b->draw();
        }

        // Update the window
        window.display();
    }

    return 0;
}

void createBall() {
    float speed = RandomInt(5, 20);
    sf::Vector2<float> pos{ (float)RandomInt(0,window.getSize().x - 40), (float)RandomInt(0,window.getSize().y - 40) };
    float angle = RandomInt(0, 359);
    AllBalls.push_back(new Ball(speed, pos, angle));
}