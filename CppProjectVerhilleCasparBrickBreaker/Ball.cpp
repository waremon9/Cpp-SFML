#include "Ball.h"
#include <iostream>

class Brick;

Ball::Ball(float speed, sf::Vector2<float> position, float angle) : ShapeEntity(position)
{
    Velocity = speed;
    _Shape = new sf::CircleShape{ Radius, 20 };
    _Shape->setPosition(Position);
    Direction = normalizeVector(sf::Vector2<float> { cos(angle), sin(angle) });

    Direction * 2.0f;
}

//take the surface normal of obstacle and change velocity so the ball bounce
void Ball::Bounce( sf::Vector2<float> n) {
    //split velocity into u perpendiculat to surface and w parallel to it
    sf::Vector2<float> u = dotProduct(Direction, n) * n;
    sf::Vector2<float> w = Direction - u;
    //update ballSpeed
    Direction = w - u;
}

void Ball::Move() {
    //update ball position
    Position += Direction * Velocity * deltaTime;
    _Shape->setPosition(Position);
}
