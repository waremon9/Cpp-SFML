#pragma once
#include "ShapeEntity.h"
class Bouton : public ShapeEntity
{

private:
	sf::Text* BoutonText;

public:
	Bouton();

	void draw() const override;

};

