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

//return random float between min and max (ty stacko)
float RandomFloat(float min, float max) {
    return min + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (max - min)));
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
    sf::FloatRect Bound1 = E1->getGlobalBounds();
    sf::FloatRect Bound2 = E2->getGlobalBounds();
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
    sf::FloatRect Bound1 = E1->getGlobalBounds();
    sf::FloatRect Bound2 = E2->getGlobalBounds();
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
    sf::FloatRect Bound1 = E1->getGlobalBounds();
    sf::FloatRect Bound2 = E2->getGlobalBounds();
    sf::Vector2<float> circle1Center{ (Bound1.left + Bound1.width / 2) , (Bound1.top + Bound1.height / 2) };
    sf::Vector2<float> circle2Center{ (Bound2.left + Bound2.width / 2) , (Bound2.top + Bound2.height / 2) };

    //get distance between circle1 center and circle2 center
    float distance = distance2Points(circle1Center, circle2Center);

    return distance < Bound1.width / 2 + Bound2.width / 2;
}

void CheckCollisions(std::vector<Brick*> allBricks, std::vector<Ball*> allBalls, std::vector<GameBorder*> allBorders)
{
    int ballIndex = 1;
    for (Ball* ball : allBalls) {

        bool hitSomething = false;

        for (Brick* brick : allBricks)
        {
            if (intersects(ball, brick))
            {
                if (!vectorContain(ball->getCollisionVector(), brick))
                {
                    if (!hitSomething)
                    {//first hit, update direction
                        ball->clearInCollisionVector();

                        Entity::Side result = whichSide(ball, brick);

                        switch (result)
                        {
                        case Entity::Side::TOP:
                        case Entity::Side::BOTTOM:
                            ball->inverseDirectionY();
                            break;
                        case Entity::Side::LEFT:
                        case Entity::Side::RIGHT:
                            ball->inverseDirectionX();
                            break;
                        default:
                            break;
                        }

                        hitSomething = true;
                    }

                    ball->addInCollisionVector(brick);
                    brick->damage();
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

    for (Brick* b : AllBricks) {
        if (b->getLife() <= 0) {
            blockToDelete.push_back(index);
        }
        index++;
    }

    for (int i = blockToDelete.size() - 1; i >= 0; i--) {


        //WARNING!!! Un peu barbare mais c'est pour tester si ca fonctionne

        AllParticleEmitters.push_back(
            new ParticleEmitter(
                AllBricks[blockToDelete[i]]->getPosition() + ((sf::RectangleShape*)AllBricks[blockToDelete[i]]->getShape())->getSize() / 2.f,
                new ParticleSimple(
                    new sf::CircleShape(2.7, 10)
                ),
                0.1,
                0.004,
                3,
                sf::Vector2f(0.12, 0.4),
                sf::Vector2f(100, 250),
                sf::Vector2f(0, 360),
                sf::Color::Red
            )
        );

        //Fin du warning. A la prochaine.

        delete AllBricks[blockToDelete[i]];
        AllBricks.erase(AllBricks.begin() + blockToDelete[i]);
    }
}

void removeParticle() {
    std::vector<int> particleToDelete;
    int index = 0;

    for (Particle* p : AllParticles) {
        if (p->getLifeTime() <= 0) {
            particleToDelete.push_back(index);
        }
        index++;
    }

    for (int i = particleToDelete.size() - 1; i >= 0; i--) {
        delete AllParticles[particleToDelete[i]];
        AllParticles.erase(AllParticles.begin() + particleToDelete[i]);
    }
}

void removeParticleEmitter() {
    std::vector<int> particleEmitterToDelete;
    int index = 0;

    for (ParticleEmitter* pe : AllParticleEmitters) {
        if (pe->getEmitterLifeTime() <= 0) {
            particleEmitterToDelete.push_back(index);
        }
        index++;
    }

    for (int i = particleEmitterToDelete.size() - 1; i >= 0; i--) {
        delete AllParticleEmitters[particleEmitterToDelete[i]];
        AllParticleEmitters.erase(AllParticleEmitters.begin() + particleEmitterToDelete[i]);
    }
}