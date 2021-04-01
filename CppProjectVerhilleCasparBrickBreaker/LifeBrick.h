#pragma once
#include "Brick.h"

//brick with more than 1 life
class LifeBrick : public Brick
{
protected:
	sf::Text* TextNumber = new sf::Text;
	int HitScore;

	void UpdateTextNumber();

public:
	LifeBrick(sf::Vector2f, sf::Vector2i, int, sf::Font*);//Position, Life amount

	virtual int getHitScore();

	void draw() const override;
	void damage() override;
};

