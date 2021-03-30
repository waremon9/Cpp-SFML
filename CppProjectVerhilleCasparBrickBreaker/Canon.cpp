#include "Canon.h"
#include "Ball.h"

Canon::Canon()
{
	Angle = 0;

	BaseCooldown = 0.3f;
	Cooldown = BaseCooldown;
	BallSpeed = 800;

	//Canon sprite
	_Sprite = new sf::Sprite;

	_Texture = new sf::Texture;
	_Texture->loadFromFile("canon.png");
	_Texture->setSmooth(true);

	_Sprite->setTexture(*_Texture);

	//Particle sprite
	sf::Sprite* spr = new sf::Sprite;

	sf::Texture* tex = new sf::Texture;
	tex->loadFromFile("explosionParticle.png");
	tex->setSmooth(true);

	spr->setTexture(*tex);
	spr->setScale(0.08, 0.08);

	ShootParticle = new ParticleComplex(
		spr,
		5,
		true
	);

	GameManager* GM = GameManager::getInstance();

	//position and size
	Position = sf::Vector2f(GM->getWindow()->getSize().x / 2, GM->getWindow()->getSize().y);
	_Sprite->setPosition(Position);
	
	sf::FloatRect Bound = _Sprite->getGlobalBounds();

	Origin = sf::Vector2f(Bound.width / 2, Bound.height / 6 * 4.65);
	_Sprite->setOrigin(Origin);

	_Sprite->setScale(0.22,0.22);

	//Shoot sound
	Buffer = new sf::SoundBuffer;
	Buffer->loadFromFile("Piou.wav");
	ShootSound = new sf::Sound();
	ShootSound->setBuffer(*Buffer);
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
	GameManager* GM = GameManager::getInstance();

	if (Cooldown<=0 && GM->getAllBalls().size()<3) {
		Ball* ball = new Ball(BallSpeed, sf::Vector2f(0,0), Angle);
		ball->getShape()->setOrigin(sf::Vector2f(ball->getRadius(), ball->getRadius()));
		sf::Vector2f canonFront = Position + Direction * _Sprite->getOrigin().y * _Sprite->getScale().y;
		ball->setPosition(canonFront);
		GM->getAllBalls().push_back(ball);

		

		float calculatedAngle = Angle * 180 / 3.1415 + 90;

		GM->getAllParticleEmitters().push_back(
			new ParticleEmitter(
				canonFront - sf::Vector2f(45,40),
				ShootParticle,
				0.001,
				0.001,
				30,
				sf::Vector2f(0.2, 0.5),
				sf::Vector2f(150, 300),
				sf::Vector2f(calculatedAngle - 30,calculatedAngle - 150),
				sf::Color(255, 255, 255, 20)
			)
		);

		ShootSound->play();

		ResetCooldown();
	}

}

void Canon::update(float dt)
{
	Cooldown -= dt;
}
