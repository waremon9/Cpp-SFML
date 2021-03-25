#include "ExplosiveBrick.h"
#include "Explosion.h"
#include "Function.h"
#include <iostream>

ExplosiveBrick::ExplosiveBrick(sf::Vector2<float> pos) : Brick(pos)
{
	ExplosiveRange = 30;
	AlreadyExplode = false;

	FillColor = sf::Color(101, 67, 33);
	OutlineColor = sf::Color(153, 62, 0);

	_Shape->setFillColor(FillColor);
	_Shape->setOutlineColor(OutlineColor);
}

void ExplosiveBrick::explode()
{
	Explosion* boom = new Explosion(Position + ((sf::RectangleShape*)_Shape)->getSize() / 2.f, new sf::RectangleShape(((sf::RectangleShape*)_Shape)->getSize() + sf::Vector2f(ExplosiveRange*2, ExplosiveRange * 2)));

	for (Brick* b : AllBricks) {
		if (b != this) {
			if (intersects(boom, b)) {
				b->damage();
			}
		}
	}

	delete boom;
}

void ExplosiveBrick::damage()
{
	Brick::damage();

	if (!AlreadyExplode) {
		AlreadyExplode = true;
		explode();
	}
}
