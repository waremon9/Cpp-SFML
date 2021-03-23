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
    Position += Direction * Velocity * deltaTime;
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
            whichSide(*Circle, b->getShape());
        }
    }

    for (Ball* b : allBalls) {
        if (b->getPosition() != Position) {//not checking with herself
            if (intersects(*Circle, b->getShape())) {
                /*
                Bounce(ballNormal(*Circle, b->getShape()));
                b->Bounce(ballNormal(b->getShape(), *Circle));
                */
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

/*
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
*/

bool Ball::intersects(sf::CircleShape circle, sf::RectangleShape rect) {
    if (
        circle.getPosition().x < rect.getPosition().x + rect.getSize().x && //gauche circle and droite rectangle
        circle.getPosition().x + circle.getRadius() * 2 > rect.getPosition().x && //droite circle and gauche rectangle
        circle.getPosition().y < rect.getPosition().y + rect.getSize().y && //haut circle and bas rectangle
        circle.getPosition().y + circle.getRadius() * 2 > rect.getPosition().y) { //bas circle and haut rectangle
        return true;
    }
    return false;
}

void Ball::whichSide(sf::CircleShape circle, sf::RectangleShape rect) {
    float droite = distance2Points(circle.getPosition() + sf::Vector2<float>{0, circle.getRadius()}, rect.getPosition() + sf::Vector2<float>{rect.getSize().x, -rect.getSize().y / 2});
    float gauche = distance2Points(circle.getPosition() + sf::Vector2<float>{circle.getRadius() * 2, -circle.getRadius()}, rect.getPosition() + sf::Vector2<float>{0, -rect.getSize().y / 2});
    float haut = distance2Points(circle.getPosition() + sf::Vector2<float>{circle.getRadius(), circle.getRadius() * 2}, rect.getPosition() + sf::Vector2<float>{rect.getSize().x / 2, 0});
    float bas = distance2Points(circle.getPosition() + sf::Vector2<float>{circle.getRadius(), 0}, rect.getPosition() + sf::Vector2<float>{rect.getSize().x / 2, rect.getSize().y});
    float konami = std::min({ droite, gauche, haut, bas });
    if (konami == droite) Direction.x *= -1;
    else if (konami == gauche) Direction.x *= -1;
    else if (konami == haut) Direction.y *= -1;
    else if (konami == bas) Direction.y *= -1;
}

bool Ball::intersects(sf::CircleShape circle1, sf::CircleShape circle2)
{
    sf::Vector2<float> circle1Center{ (circle1.getPosition().x + circle1.getRadius()) , (circle1.getPosition().y + circle1.getRadius()) };
    sf::Vector2<float> circle2Center{ (circle2.getPosition().x + circle2.getRadius()) , (circle2.getPosition().y + circle2.getRadius()) };

    //get distance between circle1 center and circle2 center
    float distance = distance2Points(circle1Center, circle2Center);

    return distance < circle1.getRadius() + circle2.getRadius();
}

/*
sf::Vector2<float> Ball::ballNormal(sf::CircleShape circle1, sf::CircleShape circle2) {
    sf::Vector2<float> circle1Center{ (circle1.getPosition().x + circle1.getRadius()) , (circle1.getPosition().y + circle1.getRadius()) };
    sf::Vector2<float> circle2Center{ (circle2.getPosition().x + circle2.getRadius()) , (circle2.getPosition().y + circle2.getRadius()) };

    return normalizeVector( circle1Center - circle2Center );
}
*/