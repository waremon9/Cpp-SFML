#include "Canon.h"
#include "Ball.h"
#include "SoundManager.h"
#include "RessourceManager.h"

Canon::Canon()
{
	RessourceManager* RM = RessourceManager::getInstance();

	Angle = 0;

	BaseCooldown = 0.3f;
	Cooldown = BaseCooldown;
	BallSpeed = 800;

	//Canon sprite
	_Sprite = new sf::Sprite;
	_Sprite->setTexture(*RM->getTexture(RessourceManager::Canon));

	//Particle sprite
	sf::Sprite* spr = new sf::Sprite;
	spr->setTexture(*RM->getTexture(RessourceManager::ExplosionPart));
	spr->setScale(0.08f, 0.08f);

	ShootParticle = new ParticleComplex(
		spr,
		5,
		true
	);

	GameManager* GM = GameManager::getInstance();

	//position and size
	Position = sf::Vector2f(GM->getWindow()->getSize().x / 2.f, GM->getWindow()->getSize().y);
	_Sprite->setPosition(Position);
	
	sf::FloatRect Bound = _Sprite->getGlobalBounds();

	_Sprite->setScale(0.22f,0.22f);

	Origin = sf::Vector2f(Bound.width / 2, Bound.height / 6 * 4.65);
	_Sprite->setOrigin(Origin);
}

void Canon::setRotation(float angle)
{
	float calculatedAngle = angle * 180.f / 3.1415f + 90;
	if (calculatedAngle >= -70 && calculatedAngle <= 70) {
		Angle = angle;
		_Sprite->setRotation(calculatedAngle);
		Direction = normalizeVector(sf::Vector2<float> { cos(angle), sin(angle) });
	}
	
}

void Canon::shoot()
{
	GameManager* GM = GameManager::getInstance();

	if (Cooldown<=0 && GM->getBallAmount() > 0) {
		Ball* ball = new Ball(BallSpeed, sf::Vector2f(0,0), Angle);
		sf::Vector2f canonFront = Position + Direction * _Sprite->getOrigin().y * _Sprite->getScale().y;
		ball->setPosition(canonFront);
		GM->getAllBalls().push_back(ball);

		float calculatedAngle = Angle * 180 / 3.1415f + 90;

		GM->getAllParticleEmitters().push_back(
			new ParticleEmitter(
				canonFront - sf::Vector2f(45,40),
				ShootParticle,
				0.001,
				0.001,
				30,
				sf::Vector2f(0.2f, 0.5f),
				sf::Vector2f(150.f, 300.f),
				sf::Vector2f(calculatedAngle - 30, calculatedAngle - 150),
				sf::Color(255, 255, 255, 20)
			)
		);

		SoundManager::getInstance()->playSound(SoundManager::SoundLabel::Piou);

		ResetCooldown();
		GM->useBall();
	}

}

void Canon::update(float dt)
{
	Cooldown -= dt;
}
