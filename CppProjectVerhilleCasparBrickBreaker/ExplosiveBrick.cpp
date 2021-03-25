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

	sf::Texture* bomb = new sf::Texture;
	bomb->loadFromFile("BombIcon.png");
	bomb->setSmooth(true);
	BombIcon = new sf::Sprite();
	BombIcon->setTexture(*bomb);
	sf::FloatRect bombBound = BombIcon->getGlobalBounds();
	BombIcon->setOrigin(sf::Vector2f(bombBound.width / 2, bombBound.height / 2));
	BombIcon->setPosition(Position + ((sf::RectangleShape*)_Shape)->getSize() / 2.f);
	BombIcon->setScale(0.2, 0.2);
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

void ExplosiveBrick::draw() const {
	Brick::draw();
	window.draw(*BombIcon);
}
