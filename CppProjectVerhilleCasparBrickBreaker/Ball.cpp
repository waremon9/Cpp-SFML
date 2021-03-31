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

    _Sprite->setOrigin(sf::Vector2f{ _Sprite->getGlobalBounds().width / 2.f, _Sprite->getGlobalBounds().height / 2.f });
}

void Ball::playHitSound()
{
    SoundManager::getInstance()->playSound(SoundManager::SoundLabel::Toc);
}

void Ball::spawnParticleHit(sf::Vector2f pos, float angle)
{
    GameManager* GM = GameManager::getInstance();

    Particle* p = new ParticleSimple(
        new sf::CircleShape(1.2, 8),
        0,
        false
    );

    GM->getAllParticleEmitters().push_back(
        new ParticleEmitter(
            pos,
            p,
            0.001,
            0.001,
            18,
            sf::Vector2f(0.08, 0.3),
            sf::Vector2f(70, 120),
            sf::Vector2f(angle + 20, angle - 20),
            sf::Color(200, 200, 200, 150)
        )
    );

    GM->getAllParticleEmitters().push_back(
        new ParticleEmitter(
            pos,
            p,
            0.001,
            0.001,
            18,
            sf::Vector2f(0.08, 0.3),
            sf::Vector2f(70, 120),
            sf::Vector2f(angle + 200, angle + 160),
            sf::Color(200,200,200,150)
        )
    );
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
