#include "ExplosiveBrick.h"
#include "Function.h"
#include "NomMarrantTableauUneDimension.h"
#include <iostream>

ExplosiveBrick::ExplosiveBrick(sf::Vector2f pos, sf::Vector2i coord) : Brick(pos, coord)
{
	ExplosiveRange = 30;
	AlreadyExplode = false;

	//brick color
	FillColor = sf::Color(101, 67, 33);
	OutlineColor = sf::Color(153, 62, 0);

	_Shape->setFillColor(FillColor);
	_Shape->setOutlineColor(OutlineColor);

	//Bomb icon
	sf::Texture* bomb = new sf::Texture;
	bomb->loadFromFile("BombIcon.png");
	bomb->setSmooth(true);
	BombIcon = new sf::Sprite();
	BombIcon->setTexture(*bomb);
	sf::FloatRect bombBound = BombIcon->getGlobalBounds();
	BombIcon->setOrigin(sf::Vector2f(bombBound.width / 2, bombBound.height / 2));
	BombIcon->setPosition(Position + ((sf::RectangleShape*)_Shape)->getSize() / 2.f);
	BombIcon->setScale(0.2, 0.2);

	//Particle sprite
	sf::Sprite* spr = new sf::Sprite;

	sf::Texture* tex = new sf::Texture;
	tex->loadFromFile("explosionParticle.png");
	tex->setSmooth(true);

	spr->setTexture(*tex);
	spr->setScale(0.08, 0.08);

	ExplosionParticle = new ParticleComplex(
		spr,
		5,
		true
	);

	//hit sound
	Buffer = new sf::SoundBuffer;
	Buffer->loadFromFile("Boom.wav");
	BoomSound = new sf::Sound();
	BoomSound->setBuffer(*Buffer);
	BoomSound->setVolume(25);
}

void ExplosiveBrick::explode()
{
	BoomSound->play();

	AllParticleEmitters.push_back(
		new ParticleEmitter(
			Position,
			ExplosionParticle,
			0.001,
			0.001,
			70,
			sf::Vector2f(0.3, 0.7),
			sf::Vector2f(250, 450),
			sf::Vector2f(0,360),
			sf::Color(220, 220, 180, 70)
		)
	);

	if (Coordinate.x != 0 && BricksTableau->getBrickAt(Coordinate.x - 1, Coordinate.y) != nullptr) BricksTableau->getBrickAt(Coordinate.x - 1, Coordinate.y)->damage();
	if (Coordinate.x != BricksTableau->getWidth() - 1 && BricksTableau->getBrickAt(Coordinate.x + 1, Coordinate.y) != nullptr) BricksTableau->getBrickAt(Coordinate.x + 1, Coordinate.y)->damage();
	if (Coordinate.y != 0 && BricksTableau->getBrickAt(Coordinate.x, Coordinate.y - 1) != nullptr) BricksTableau->getBrickAt(Coordinate.x, Coordinate.y - 1)->damage();
	if (Coordinate.y != BricksTableau->getHeight() - 1 && BricksTableau->getBrickAt(Coordinate.x, Coordinate.y + 1) != nullptr) BricksTableau->getBrickAt(Coordinate.x, Coordinate.y + 1)->damage();

	if (Coordinate.x != 0 && Coordinate.y != 0 && BricksTableau->getBrickAt(Coordinate.x - 1, Coordinate.y - 1) != nullptr) BricksTableau->getBrickAt(Coordinate.x - 1, Coordinate.y - 1)->damage();
	if (Coordinate.x != BricksTableau->getWidth() - 1 && Coordinate.y != 0 && BricksTableau->getBrickAt(Coordinate.x + 1, Coordinate.y - 1) != nullptr) BricksTableau->getBrickAt(Coordinate.x + 1, Coordinate.y - 1)->damage();
	if (Coordinate.x != 0 && Coordinate.y != BricksTableau->getHeight() - 1 && BricksTableau->getBrickAt(Coordinate.x - 1, Coordinate.y + 1) != nullptr) BricksTableau->getBrickAt(Coordinate.x - 1, Coordinate.y + 1)->damage();
	if (Coordinate.x != BricksTableau->getWidth() - 1 && Coordinate.y != BricksTableau->getHeight() - 1 && BricksTableau->getBrickAt(Coordinate.x + 1, Coordinate.y + 1) != nullptr) BricksTableau->getBrickAt(Coordinate.x + 1, Coordinate.y + 1)->damage();


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
