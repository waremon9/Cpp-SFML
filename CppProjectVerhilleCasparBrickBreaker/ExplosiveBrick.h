#pragma once
#include "Brick.h"

class ExplosiveBrick : public Brick
{
private:
	float ExplosiveRange;
	bool AlreadyExplode;

	sf::Sprite* BombIcon;

	void explode();

public:
	ExplosiveBrick(sf::Vector2<float>); //position

	void damage() override;
	void draw() const override;
};

