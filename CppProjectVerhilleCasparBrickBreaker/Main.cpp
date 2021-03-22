#include <iostream>
#include <SFML/Graphics.hpp>
#include "Global.h"
#include "Function.h"
#include "Ball.h"
#include "Block.h"

void createBall();

sf::RenderWindow window(sf::VideoMode(1050,700), "HelloWorld");

std::vector<Ball*> AllBalls;
std::vector<Block*> AllBricks;

int main()
{
    srand(time(NULL));//make random really random

    //window
    window.setFramerateLimit(60);

    //ball
    for (int i = 0; i < 10; i++) {
        createBall();
    }

    //bricks
    AllBricks.push_back(new Block(sf::Vector2<float>{200, 200}));
    AllBricks.push_back(new Block(sf::Vector2<float>{600, 200}));
    AllBricks.push_back(new Block(sf::Vector2<float>{500, 400}));

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
            b->CheckColisions(AllBricks);
        }

        // Clear screen
        window.clear();
        //draw everything
        for (Ball* b : AllBalls) {
            b->draw();
        }
        for (Block* b : AllBricks) {
            b->draw();
        }

        // Update the window
        window.display();
    }

    return 0;
}

void createBall() {
    float speed = RandomInt(5, 8);
    sf::Vector2<float> pos{ (float)RandomInt(0,window.getSize().x - 40), (float)RandomInt(0,window.getSize().y - 40) };
    float angle = RandomInt(0, 359);
    AllBalls.push_back(new Ball(speed, pos, angle));
}