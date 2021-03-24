#pragma once
#include <SFML/Graphics.hpp>

class Ball;
class Block;

extern sf::RenderWindow window;
extern float deltaTime;
extern std::vector<Ball*> AllBalls;
extern std::vector<Block*> AllBricks;