#pragma once
#include "Entity.h"

class ShapeEntity : public Entity
{
protected:
	sf::Shape* _Shape = nullptr;

public:
	ShapeEntity() {};
	ShapeEntity(sf::Vector2f);

	sf::Shape* getShape() const { return _Shape; }
	sf::FloatRect getGlobalBounds() const override { return _Shape->getGlobalBounds(); }

	virtual void draw() const override { GameManager::getInstance()->getWindow()->draw(*_Shape); }
};

