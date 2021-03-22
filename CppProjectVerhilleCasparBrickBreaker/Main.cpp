#include <iostream>
#include <SFML/Graphics.hpp>
#include "Global.h"
#include "Function.h"
#include "Ball.h"

sf::RenderWindow window(sf::VideoMode(1050,700), "HelloWorld");

int main()
{
    srand(time(NULL));//make random really random

    //window
    window.setFramerateLimit(60);

    //ball
    Ball ball(8, sf::Vector2<float> { 500,350 }, RandomInt(0, 359));

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

        ball.Move();

        // Clear screen
        window.clear();
        //draw everything
        ball.draw();

        // Update the window
        window.display();
    }

    return 0;
}