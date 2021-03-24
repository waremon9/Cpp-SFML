#include "RegenBrick.h"

RegenBrick::RegenBrick(sf::Vector2f pos, int life, sf::Font* font) : LifeBrick(pos, life, font)
{
	MaxLife = life;

	sf::Color FillColor = sf::Color(60, 220, 60);
	sf::Color OutlineColor = sf::Color(180, 255, 180);

	_Shape->setFillColor(FillColor);
	_Shape->setOutlineColor(OutlineColor);

	TextNumber->setFont(*font);
	UpdateTextNumber();
}

void RegenBrick::RegenLife()
{
	if (Life < MaxLife) {
		Life++;
		UpdateTextNumber();
	}
}
