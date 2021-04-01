#pragma once
#include "LifeBrick.h"

class RegenBrick : public LifeBrick
{
private: 
	int MaxLife;
	float BaseRegenCooldown;
	float RegenCooldown;
	int HitNumber;

	void RegenLife();
	void resetCooldown() { RegenCooldown = BaseRegenCooldown; }

public:
	RegenBrick(sf::Vector2f, sf::Vector2i, int, sf::Font*);//Position, Life amount
	int getHitScore() override;
	void update(float) override;
};

