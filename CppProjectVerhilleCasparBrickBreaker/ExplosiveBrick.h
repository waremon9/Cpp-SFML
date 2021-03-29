#pragma once
#include "Brick.h"
#include <SFML/Audio.hpp>

class ExplosiveBrick : public Brick
{
private:
	float ExplosiveRange;
	bool AlreadyExplode;

	sf::Sprite* BombIcon;

	sf::SoundBuffer* Buffer = nullptr;
	sf::Sound* BoomSound = nullptr;

	void explode();

public:
	ExplosiveBrick(sf::Vector2<float>); //position

	void damage() override;
	void draw() const override;
};