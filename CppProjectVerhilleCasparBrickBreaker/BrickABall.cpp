#include "BrickABall.h"
#include "RessourceManager.h"

BrickABall::BrickABall(sf::Vector2f pos, sf::Vector2i coord) : Brick(pos, coord)
{
	//bool to be sure the ball isn't given more than once
	BallGiven = false;

	//brick color
	FillColor = sf::Color(100, 150, 255);
	OutlineColor = sf::Color(80, 200, 200);

	_Shape->setFillColor(FillColor);
	_Shape->setOutlineColor(OutlineColor);

	//Ball icon
	BallIcon = new sf::Sprite;
	BallIcon->setTexture(*RessourceManager::getInstance()->getTexture(RessourceManager::Ball));
	BallIcon->setScale(sf::Vector2f(0.8, 0.8));
	sf::FloatRect ballBound = BallIcon->getGlobalBounds();
	BallIcon->setOrigin(sf::Vector2f(ballBound.width / 2, ballBound.height / 2));
	BallIcon->setPosition(Position + ((sf::RectangleShape*)_Shape)->getSize() / 2.f);
}

void BrickABall::damage()
{
	Brick::damage();
	//player get a bonus ball
	if (!BallGiven) {
		gimmeBall();
		BallGiven = true;
	}
}

void BrickABall::draw() const {
	Brick::draw();
	GameManager::getInstance()->getWindow()->draw(*BallIcon);
}

void BrickABall::gimmeBall() {
	GameManager::getInstance()->addBall();
}