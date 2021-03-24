#define _USE_MATH_DEFINES
#include "Function.h"
#include <random>
#include <SFML/Graphics.hpp>
#include <algorithm>
#include <iostream>

//return random int between min(include) and max(include)
int RandomInt(int min, int max) {
    return rand() % (max - min + 1) + min;
}

//convert degree to radian
float convertToRadian(float degree) {
    return (degree * (M_PI / 180));
}

//normalize a vector2
sf::Vector2<float> normalizeVector(sf::Vector2<float> vect) {
    float mag = sqrt(vect.x * vect.x + vect.y * vect.y);
    return vect / mag;
}

//get the surface normal of a segment (from left to right)
sf::Vector2<float> getNormalVector(sf::Vector2<float> segStart, sf::Vector2<float> segEnd) {
    sf::Vector2<float> normal{ -(segEnd.y - segStart.y), (segEnd.x - segStart.x) };
    return normalizeVector(normal);
}

//return the dot product of 2 vector2
float dotProduct(sf::Vector2<float> vect1, sf::Vector2<float> vect2) {
    return vect1.x * vect2.x + vect1.y * vect2.y;
}

//return the distance between 2 points
float distance2Points(sf::Vector2<float> p1, sf::Vector2<float> p2) {
    return abs(sqrt((p2.x - p1.x)* (p2.x - p1.x) + (p2.y - p1.y) * (p2.y - p1.y)));
}

bool vectorContain(const std::vector<Entity*>& v, Entity* elem) {
    if (std::find(v.begin(), v.end(), elem) != v.end()) {
        return true;
    }
    return false;
}

bool intersects(const Entity* E1, const Entity* E2)  {
    sf::FloatRect Bound1 = E1->getShape()->getGlobalBounds();
    sf::FloatRect Bound2 = E2->getShape()->getGlobalBounds();
    if (
        Bound1.left < Bound2.left + Bound2.width && 
        Bound1.left + Bound1.width > Bound2.left && 
        Bound1.top < Bound2.top + Bound2.height && 
        Bound1.top + Bound1.height > Bound2.top) { 
        return true;
    }
    return false;
}

Entity::Side whichSide(const Entity* E1, const Entity* E2) {
    sf::FloatRect Bound1 = E1->getShape()->getGlobalBounds();
    sf::FloatRect Bound2 = E2->getShape()->getGlobalBounds();
    float droite = abs(Bound1.left - (Bound2.left + Bound2.width));
    float gauche = abs((Bound1.left + Bound1.width) - Bound2.left);
    float haut = abs((Bound1.top + Bound1.height) - Bound2.top);
    float bas = abs(Bound1.top - (Bound2.top + Bound2.height));
    float konami = std::min({ droite, gauche, haut, bas });
    if (konami == droite) return Entity::Side::RIGHT;
    else if (konami == gauche)  return Entity::Side::LEFT;
    else if (konami == haut)  return Entity::Side::TOP;
    else if (konami == bas)  return Entity::Side::BOTTOM;
}

bool ballIntersects(const Entity* E1, const Entity* E2) {
    sf::FloatRect Bound1 = E1->getShape()->getGlobalBounds();
    sf::FloatRect Bound2 = E2->getShape()->getGlobalBounds();
    sf::Vector2<float> circle1Center{ (Bound1.left + Bound1.width / 2) , (Bound1.top + Bound1.height / 2) };
    sf::Vector2<float> circle2Center{ (Bound2.left + Bound2.width / 2) , (Bound2.top + Bound2.height / 2) };

    //get distance between circle1 center and circle2 center
    float distance = distance2Points(circle1Center, circle2Center);

    return distance < Bound1.width / 2 + Bound2.width / 2;
}

void CheckCollisions(std::vector<Block*> allBricks, std::vector<Ball*> allBalls, std::vector<GameBorder*> allBorders)
{
    int ballIndex = 1;
    for (Entity* ball : allBalls) {

        bool hitSomething = false;

        for (Entity* brick : allBricks)
        {
            if (intersects(ball, brick))
            {
                if (!vectorContain(((Ball*)ball)->getCollisionVector(), brick))
                {
                    if (!hitSomething)
                    {//first hit, update direction
                        ((Ball*)ball)->clearInCollisionVector();

                        Entity::Side result = whichSide(ball, brick);

                        switch (result)
                        {
                        case Entity::Side::TOP:
                        case Entity::Side::BOTTOM:
                            ((Ball*)ball)->inverseDirectionY();
                            break;
                        case Entity::Side::LEFT:
                        case Entity::Side::RIGHT:
                            ((Ball*)ball)->inverseDirectionX();
                            break;
                        default:
                            break;
                        }

                        hitSomething = true;
                    }

                    ((Ball*)ball)->addInCollisionVector(brick);
                    ((Block*)brick)->damage();
                }
            }
        }

        for (Entity* border : allBorders)
        {
            if (intersects(ball, border))
            {
                if (!vectorContain(((Ball*)ball)->getCollisionVector(), border))
                {
                    if (!hitSomething)
                    {//first hit, update direction
                        ((Ball*)ball)->clearInCollisionVector();

                        Entity::Side result = whichSide(ball, border);

                        switch (result)
                        {
                        case Entity::Side::TOP:
                        case Entity::Side::BOTTOM:
                            ((Ball*)ball)->inverseDirectionY();
                            break;
                        case Entity::Side::LEFT:
                        case Entity::Side::RIGHT:
                            ((Ball*)ball)->inverseDirectionX();
                            break;
                        default:
                            break;
                        }

                        hitSomething = true;
                    }

                    ((Ball*)ball)->addInCollisionVector(border);
                }
            }
        }


        for (int i = ballIndex; i < allBalls.size(); i++ ) {
            if (intersects(ball, allBalls[i]))
            {
                if (!vectorContain(((Ball*)ball)->getCollisionVector(), allBalls[i]))
                {
                    if (!hitSomething) {//first hit, update direction
                        ((Ball*)ball)->clearInCollisionVector();
                        allBalls[i]->clearInCollisionVector();

                        sf::Vector2<float> tmpDir = ((Ball*)ball)->getDirection();
                        ((Ball*)ball)->setDirection(allBalls[i]->getDirection());
                        allBalls[i]->setDirection(tmpDir);
                        float tmpVel = ((Ball*)ball)->getVelocity();
                        ((Ball*)ball)->setVelocity(allBalls[i]->getVelocity());
                        allBalls[i]->setVelocity(tmpVel);

                        hitSomething = true;
                    }

                    ((Ball*)ball)->addInCollisionVector(allBalls[i]);
                    allBalls[i]->addInCollisionVector(ball);
                }
            }
        }
        ballIndex++;
    }
    

    
}

void removeOuOfBoundBall() {
    std::vector<int> ballToDelete;
    int index = 0;

    for (Ball* b : AllBalls) {
        if (b->getPosition().y>window.getSize().y + b->getRadius()) {
            ballToDelete.push_back(index);
        }
        index++;
    }

    for (int i = ballToDelete.size() - 1; i >= 0; i--) {
        delete AllBalls[ballToDelete[i]];
        AllBalls.erase(AllBalls.begin() + ballToDelete[i]);
    }
}

void removeDeadBlock() {
    std::vector<int> blockToDelete;
    int index = 0;

    for (Block* b : AllBricks) {
        if (b->getLife() <= 0) {
            blockToDelete.push_back(index);
        }
        index++;
    }

    for (int i = blockToDelete.size() - 1; i >= 0; i--) {
        delete AllBricks[blockToDelete[i]];
        AllBricks.erase(AllBricks.begin() + blockToDelete[i]);
    }
}