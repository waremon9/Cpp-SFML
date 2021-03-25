#pragma once
#include "Entity.h"
class SpriteEntity : public Entity
{
protected:
	sf::Sprite* _Sprite = nullptr;

public:
	SpriteEntity() {};
	SpriteEntity(sf::Vector2f);

	sf::Sprite* getShape() const { return _Sprite; }
	sf::FloatRect getGlobalBounds() const override { return _Sprite->getGlobalBounds(); }

	virtual void draw() const override { window.draw(*_Sprite); }
};

