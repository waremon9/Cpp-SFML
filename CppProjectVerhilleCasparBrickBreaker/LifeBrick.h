#pragma once
#include "Brick.h"

//brick with more than 1 life
class LifeBrick : public Brick
{
private:
	sf::Text* TextNumber = new sf::Text;

	void UpdateTextNumber();

public:
	LifeBrick(sf::Vector2f, int, sf::Font*);//Position, Life amount

	void draw() const ;
	void damage();
};

