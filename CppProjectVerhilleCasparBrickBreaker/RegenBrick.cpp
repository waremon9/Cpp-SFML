#include "RegenBrick.h"

RegenBrick::RegenBrick(sf::Vector2f pos, sf::Vector2i coord, int life, sf::Font* font) : LifeBrick(pos, coord, life, font)
{
	MaxLife = life;

	sf::Color FillColor = sf::Color(60, 220, 60);
	sf::Color OutlineColor = sf::Color(180, 255, 180);

	_Shape->setFillColor(FillColor);
	_Shape->setOutlineColor(OutlineColor);

	TextNumber->setFont(*font);
	UpdateTextNumber();

	BaseRegenCooldown = 3;
	RegenCooldown = BaseRegenCooldown;
}

void RegenBrick::update(float dt)
{
	if (Life != MaxLife) {
		RegenCooldown -= dt;
		if (RegenCooldown <= 0) {
			resetCooldown();
			RegenLife();
		}
	}
}


void RegenBrick::RegenLife()
{
	if (Life < MaxLife) {
		Life++;
		UpdateTextNumber();
	}
}
