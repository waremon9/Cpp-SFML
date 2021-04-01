#pragma once
#include "Brick.h"

class BrickABall : public Brick
{
private:
	sf::Sprite* BallIcon;

	void gimmeBall();
	bool BallGiven;

public:
	BrickABall(sf::Vector2f, sf::Vector2i); //position

	void damage() override;
	void draw() const override;
};

