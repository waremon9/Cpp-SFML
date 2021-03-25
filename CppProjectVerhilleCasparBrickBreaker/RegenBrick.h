#pragma once
#include "LifeBrick.h"

class RegenBrick : public LifeBrick
{
private: 
	int MaxLife;
	float BaseRegenCooldown;
	float RegenCooldown;

	void RegenLife();
	void resetCooldown() { RegenCooldown = BaseRegenCooldown; }

public:
	RegenBrick(sf::Vector2f, int, sf::Font*);//Position, Life amount
	void update(float) override;
};

