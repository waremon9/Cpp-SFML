#pragma once
#include <SFML/Graphics.hpp>

class Ball;
class Brick;

extern sf::RenderWindow window;
extern float deltaTime;
extern std::vector<Ball*> AllBalls;
extern std::vector<Brick*> AllBricks;