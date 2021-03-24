#pragma once
#include "Brick.h"

//brick with more than 1 life
class LifeBrick : public Brick
{
private:
	sf::Text* TextNumber = new sf::Text;

	sf::Color FillColor = sf::Color(255, 60, 60);
	sf::Color OutlineColor = sf::Color(255, 180, 180);

	void UpdateTextNumber();

public:
	LifeBrick(sf::Vector2f, int, sf::Font*);//Position, Life amount

	void draw() const override;
	void damage() override;
};

