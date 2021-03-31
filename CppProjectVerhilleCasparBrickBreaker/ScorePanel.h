#pragma once
#include"Entity.h"
#include <SFML/Graphics.hpp>

class ScorePanel : public Entity
{
private:
	sf::Text* _Text;
	sf::RectangleShape* Panel;

public:
	ScorePanel(sf::Vector2f);

	void updateScore(int);
	void draw() const override;

	virtual sf::FloatRect getGlobalBounds() const override { return Panel->getGlobalBounds(); }
};

