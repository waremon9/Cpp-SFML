#include "Ball.h"
#include <iostream>
#include "Block.h"

Ball::Ball(float speed, sf::Vector2<float> position, float angle)
{
    Velocity = speed;
    Position = position;
    Circle->setPosition(Position);
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
    Position += Direction * Velocity;
    Circle->setPosition(Position);

    //screen bound
    if (Position.x < 0) Bounce(sf::Vector2<float>{1, 0});
    if (Position.x > window.getSize().x - Circle->getRadius() * 2) Bounce(sf::Vector2<float>{-1, 0});
    if (Position.y < 0) Bounce(sf::Vector2<float>{0, 1});
    if (Position.y > window.getSize().y - Circle->getRadius() * 2) Bounce(sf::Vector2<float>{0, -1});
}

//check if ball hit a brick
void Ball::CheckColisions(std::vector<Block*> allBricks, std::vector<Ball*> allBalls)
{
    for (Block* b : allBricks) {
        if (intersects(*Circle, b->getShape())) {
            Direction *= -1.f;
        }
    }

    for (Ball* b : allBalls) {
        if (b->getPosition() != Position) {//not checking with herself
            if (intersects(*Circle, b->getShape())) {
                sf::Vector2<float> tmpDir = Direction;
                Direction = b->getDirection();
                b->setDirection(tmpDir);
                float tmpVel = Velocity;
                Velocity = b->getVelocity();
                b->setVelocity(tmpVel);
            }
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


bool Ball::intersects(sf::CircleShape circle1, sf::CircleShape circle2)
{
    sf::Vector2<float> circle1Center{ (circle1.getPosition().x + circle1.getRadius()) , (circle1.getPosition().y + circle1.getRadius()) };
    sf::Vector2<float> circle2Center{ (circle2.getPosition().x + circle2.getRadius()) , (circle2.getPosition().y + circle2.getRadius()) };

    //get distance between circle1 center and circle2 center
    float distance = sqrt((circle2Center.x - circle1Center.x) * (circle2Center.x - circle1Center.x) + (circle2Center.y - circle1Center.y) * (circle2Center.y - circle1Center.y));

    return distance < circle1.getRadius() + circle2.getRadius();
}