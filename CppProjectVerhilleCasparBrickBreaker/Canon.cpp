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
	float calculatedAngle = angle * 180 / 3.1415 + 90;
	if (calculatedAngle >= -70 && calculatedAngle <= 70) {
		Angle = angle;
		_Shape->setRotation(calculatedAngle);
		Direction = normalizeVector(sf::Vector2<float> { cos(angle), sin(angle) });
	}
	
}

void Canon::shoot()
{
	if (clock->getElapsedTime().asSeconds() > Cooldown && AllBalls.size()<3) {
		Ball* ball = new Ball(400, sf::Vector2f(0,0), Angle);
		ball->getShape()->setOrigin(sf::Vector2f(ball->getRadius(), ball->getRadius()));
		ball->setPosition(Position + Direction * (((sf::RectangleShape*)_Shape)->getSize().y - ball->getRadius()));
		AllBalls.push_back(ball);

		clock->restart();
	}

}
