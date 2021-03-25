#pragma once
#include "Brick.h"

class ExplosiveBrick : public Brick
{
private:
	float ExplosiveRange;
	bool AlreadyExplode;

	void explode();

public:
	ExplosiveBrick(sf::Vector2<float>); //position

	void damage() override;
};

