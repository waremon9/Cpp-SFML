#include "Ball.h"
#include <iostream>

class Brick;

Ball::Ball(float speed, sf::Vector2f position, float angle) : SpriteEntity(position)
{
    Velocity = speed;

    //ball sprite
    _Sprite = new sf::Sprite;

    _Texture = new sf::Texture;
    _Texture->loadFromFile("ball.png");
    _Texture->setSmooth(true);

    _Sprite->setTexture(*_Texture);

    _Sprite->setPosition(Position);
    Direction = normalizeVector(sf::Vector2f { cos(angle), sin(angle) });

    Direction * 2.0f;
}

void Ball::playHitSound()
{
    SoundManager::getInstance()->playSound(SoundManager::SoundLabel::Toc);
}

//take the surface normal of obstacle and change velocity so the ball bounce
void Ball::Bounce( sf::Vector2f n) {
    //split velocity into u perpendiculat to surface and w parallel to it
    sf::Vector2f u = dotProduct(Direction, n) * n;
    sf::Vector2f w = Direction - u;
    //update ballSpeed
    Direction = w - u;
}

void Ball::update(float dt)
{
    Move(dt);
}

void Ball::Move(float dt) {
    //update ball position
    Position += Direction * Velocity * dt;
    _Sprite->setPosition(Position);
}
