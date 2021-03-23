#include "Ball.h"
#include <iostream>
#include "Block.h"

Ball::Ball(float speed, sf::Vector2<float> position, float angle) : Entity(position)
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

    //screen bound
    if (Position.x < 0) {
        CollisionVector.clear();
        Direction.x *= -1;
    }
    if (Position.x > window.getSize().x - Radius * 2) {
        CollisionVector.clear();
        Direction.x *= -1;
    }
    if (Position.y < 0) {
        CollisionVector.clear();
        Direction.y *= -1;
    }
    if (Position.y > window.getSize().y - Radius * 2) {
        CollisionVector.clear();
        Direction.y *= -1;
    }
}
