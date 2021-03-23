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

//check if ball hit a brick
void Ball::CheckCollisions(std::vector<Block*> allBricks, std::vector<Ball*> allBalls)
{
    for (Entity* b : allBricks) {
        if (intersects(b) && !vectorContain(CollisionVector, b)) {
            CollisionVector.clear();
            CollisionVector.push_back(b);

            whichSide(b);
        }
    }

    for (Entity* b : allBalls) {
        if (b->getPosition() != Position) {//not checking with herself
            if (intersects(b) && !vectorContain(CollisionVector, b)) {
                CollisionVector.clear();
                CollisionVector.push_back(b);

                sf::Vector2<float> tmpDir = Direction;
                Direction = ((Ball*)b)->getDirection();
                ((Ball*)b)->setDirection(tmpDir);
                float tmpVel = Velocity;
                Velocity = ((Ball*)b)->getVelocity();
                ((Ball*)b)->setVelocity(tmpVel);

                CollisionVector.push_back(b);
            }
        }
    }
}

bool Ball::intersects(const Entity* E) const {
    sf::FloatRect Bound1 = this->getShape()->getGlobalBounds();
    sf::FloatRect Bound2 = E->getShape()->getGlobalBounds();
    if (
        Bound1.left < Bound2.left + Bound2.width && //gauche circle and droite rectangle
        Bound1.left + Bound1.width > Bound2.left && //droite circle and gauche rectangle
        Bound1.top < Bound2.top + Bound2.height && //haut circle and bas rectangle
        Bound1.top + Bound1.height > Bound2.top) { //bas circle and haut rectangle
        return true;
    }
    return false;
}

void Ball::whichSide(const Entity* E) {
    sf::FloatRect Bound1 = this->getShape()->getGlobalBounds();
    sf::FloatRect Bound2 = E->getShape()->getGlobalBounds();
    float droite = distance2Points(sf::Vector2<float>{Bound1.left, Bound1.top + Bound1.height / 2}, sf::Vector2<float>{Bound2.left + Bound2.width, Bound2.top + Bound2.height / 2});
    float gauche = distance2Points(sf::Vector2<float>{Bound1.left + Bound1.width, Bound1.top + Bound1.height / 2}, sf::Vector2<float>{Bound2.left, Bound2.top + Bound2.height / 2});
    float haut = distance2Points(sf::Vector2<float>{Bound1.left + Bound1.width / 2, Bound1.top + Bound1.height}, sf::Vector2<float>{Bound2.left + Bound2.width / 2, Bound2.top + Bound2.height});
    float bas = distance2Points(sf::Vector2<float>{Bound1.left + Bound1.width / 2, Bound1.top}, sf::Vector2<float>{Bound2.left + Bound2.width / 2, Bound2.top});
    float konami = std::min({ droite, gauche, haut, bas });
    if (konami == droite) Direction.x *= -1;
    else if (konami == gauche) Direction.x *= -1;
    else if (konami == haut) Direction.y *= -1;
    else if (konami == bas) Direction.y *= -1;
}

bool Ball::ballIntersects(const Entity* E) const {
    sf::FloatRect Bound1 = this->getShape()->getGlobalBounds();
    sf::FloatRect Bound2 = E->getShape()->getGlobalBounds();
    sf::Vector2<float> circle1Center{ (Bound1.left + Bound1.width / 2) , (Bound1.top + Bound1.height / 2) };
    sf::Vector2<float> circle2Center{ (Bound2.left + Bound2.width / 2) , (Bound2.top + Bound2.height / 2) };

    //get distance between circle1 center and circle2 center
    float distance = distance2Points(circle1Center, circle2Center);

    return distance < Bound1.width / 2 + Bound2.width / 2;
}