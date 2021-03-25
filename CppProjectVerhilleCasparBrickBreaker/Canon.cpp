#include "Canon.h"
#include "Ball.h"

Canon::Canon()
{
	Angle = 0;


	BaseCooldown = 0.3f;
	Cooldown = BaseCooldown;
	BallSpeed = 800;

	_Sprite = new sf::Sprite();

	_Texture = new sf::Texture;
	_Texture->loadFromFile("canon.png");
	_Texture->setSmooth(true);

	_Sprite->setTexture(*_Texture);


	Position = sf::Vector2f(window.getSize().x / 2, window.getSize().y);
	_Sprite->setPosition(Position);
	
	sf::FloatRect Bound = _Sprite->getGlobalBounds();

	Origin = sf::Vector2f(Bound.width / 2, Bound.height / 6 * 4.65);
	_Sprite->setOrigin(Origin);

	_Sprite->setScale(0.22,0.22);
}

void Canon::setRotation(float angle)
{
	float calculatedAngle = angle * 180 / 3.1415 + 90;
	if (calculatedAngle >= -70 && calculatedAngle <= 70) {
		Angle = angle;
		_Sprite->setRotation(calculatedAngle);
		Direction = normalizeVector(sf::Vector2<float> { cos(angle), sin(angle) });
	}
	
}

void Canon::shoot()
{
	if (Cooldown<=0 && AllBalls.size()<3) {
		Ball* ball = new Ball(BallSpeed, sf::Vector2f(0,0), Angle);
		ball->getShape()->setOrigin(sf::Vector2f(ball->getRadius(), ball->getRadius()));
		ball->setPosition(Position + Direction * _Sprite->getOrigin().y * _Sprite->getScale().y);
		AllBalls.push_back(ball);

		ResetCooldown();
	}

}

void Canon::update(float dt)
{
	Cooldown -= dt;
}
