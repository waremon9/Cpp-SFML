#include "Ball.h"
#include <iostream>
#include "Block.h"

Ball::Ball(float speed, sf::Vector2<float> position, float angle)
{
    BaseSpeed = speed;
    Position = position;
    Circle->setPosition(Position);
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
    Circle->setPosition(Position);

    //screen bound
    if (Position.x < 0) Bounce(sf::Vector2<float>{1, 0});
    if (Position.x > window.getSize().x - Circle->getRadius() * 2) Bounce(sf::Vector2<float>{-1, 0});
    if (Position.y < 0) Bounce(sf::Vector2<float>{0, 1});
    if (Position.y > window.getSize().y - Circle->getRadius() * 2) Bounce(sf::Vector2<float>{0, -1});
}

//check if ball hit a brick
void Ball::CheckColisions(std::vector<Block*> allBricks)
{
    for (Block* b : allBricks) {
        if (intersects(*Circle, b->getShape())) {
            Velocity.x *= -1;
            Velocity.y *= -1;
        }
    }
}

//check collision between a circle and a square
bool Ball::intersects(sf::CircleShape circle, sf::RectangleShape rect)
{
    sf::Vector2<float> circleCenter{ (circle.getPosition().x + circle.getRadius()) , (circle.getPosition().y + circle.getRadius()) };
    sf::Vector2<float> rectangleCenter{ (rect.getPosition().x + rect.getSize().x/2) , (rect.getPosition().y + rect.getSize().y/2) };

    //get distance between circle center and rectangle center
    sf::Vector2<float> distance;
    distance.x = abs( circleCenter.x - rectangleCenter.x );
    distance.y = abs( circleCenter.y - rectangleCenter.y );

    if (distance.x > (rect.getSize().x / 2 + circle.getRadius())) { return false; }
    if (distance.y > (rect.getSize().y / 2 + circle.getRadius())) { return false; }

    if (distance.x <= (rect.getSize().x / 2)) { return true; }
    if (distance.y <= (rect.getSize().y / 2)) { return true; }

    float cornerDistance_sq = (distance.x - rect.getSize().x / 2) * (distance.x - rect.getSize().x / 2) +
        (distance.y - rect.getSize().y / 2) * (distance.y - rect.getSize().y / 2);

    return (cornerDistance_sq <= (circle.getRadius() * circle.getRadius()));
}