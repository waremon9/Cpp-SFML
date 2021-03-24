#pragma once
#include <SFML/Graphics.hpp>
#include "Global.h"
#include "Entity.h"

class Block : public Entity
{
protected:
	int Life = 1;

public:
	Block(sf::Vector2<float>); //position

	int getLife() const { return Life; }

	void damage() { Life--; }
};

