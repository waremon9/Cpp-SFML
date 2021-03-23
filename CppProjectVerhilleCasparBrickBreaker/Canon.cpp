#include "Canon.h"
#include "Ball.h"

Canon::Canon()
{
	_Shape = new sf::RectangleShape{ sf::Vector2f(30,100) };

	Position = sf::Vector2f(window.getSize().x / 2, window.getSize().y);
	_Shape->setPosition(Position);

	Origin = sf::Vector2f(((sf::RectangleShape*)_Shape)->getSize().x / 2, ((sf::RectangleShape*)_Shape)->getSize().y / 6 * 5);
	_Shape->setOrigin(Origin);
}

void Canon::setRotation(float angle)
{
	Angle = angle;
	_Shape->setRotation(Angle * 180 / 3.1415 + 90);
	Direction = normalizeVector(sf::Vector2<float> { cos(angle), sin(angle) });
}

void Canon::shoot()
{
	Ball* ball = new Ball(400, Position + Direction * ((sf::RectangleShape*)_Shape)->getSize().y, Angle);
	AllBalls.push_back(ball);
}
