#include "Ball.h"

Ball::Ball(float speed, sf::Vector2<float> position, float angle)
{
    BaseSpeed = speed;
    Position = position;
    Velocity = sf::Vector2<float> { BaseSpeed * cos(angle), BaseSpeed * sin(angle) };
}

//take the surface normal of obstacle and change velocity so the ball bounce
void Ball::Bounce( sf::Vector2<float> n) {
    //split velocity into u perpendiculat to surface and w parallel to it
    sf::Vector2<float> u = dotProduct(Velocity, n) * n;
    sf::Vector2<float> w = Velocity - u;
    //update ballSpeed
    Velocity = w - u;
}

void Ball::Move() {
    //update ball position
    Position += Velocity;
    Circle.setPosition(Position);

    //screen bound
    if (Position.x < 0) Bounce(sf::Vector2<float>{1, 0});
    if (Position.x > window.getSize().x - Circle.getRadius() * 2) Bounce(sf::Vector2<float>{-1, 0});
    if (Position.y < 0) Bounce(sf::Vector2<float>{0, 1});
    if (Position.y > window.getSize().y - Circle.getRadius() * 2) Bounce(sf::Vector2<float>{0, -1});
}
