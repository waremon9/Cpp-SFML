#pragma once
#include "LifeBrick.h"

class RegenBrick : public LifeBrick
{
private: 
	int MaxLife;

	void RegenLife();

public:
	RegenBrick(sf::Vector2f, int, sf::Font*);//Position, Life amount

};

