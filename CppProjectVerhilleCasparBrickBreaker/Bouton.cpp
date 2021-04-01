#include "Bouton.h"
#include "RessourceManager.h"

Bouton::Bouton() : ShapeEntity()
{
	GameManager* GM = GameManager::getInstance();

	

	int Offset = 70;
	BoutonText = new sf::Text;

	Position = sf::Vector2f(Offset, GM->getWindow()->getSize().y - Offset * 1.6);

	_Shape = new sf::RectangleShape{ sf::Vector2f(90,40) };
	sf::FloatRect BoutonBound = _Shape->getGlobalBounds();

	_Shape->setOrigin(sf::Vector2f(BoutonBound.left + BoutonBound.width / 2.f, BoutonBound.top + BoutonBound.height / 2.f));
	_Shape->setPosition(Position);
	_Shape->setOutlineThickness(-5);
	_Shape->setScale(1.25f,1.25f);
	_Shape->setOutlineColor(sf::Color(180, 180, 180, 255));

	BoutonText->setString("Restart");
	BoutonText->setFont(*RessourceManager::getInstance()->getFont(RessourceManager::MLFont));
	sf::FloatRect TextBound = BoutonText->getGlobalBounds();

	BoutonText->setOrigin(sf::Vector2f(TextBound.left + TextBound.width / 2.f, TextBound.top + TextBound.height / 2.f));
	BoutonText->setPosition(_Shape->getPosition());
	BoutonText->setFillColor(sf::Color::Black);
}

void Bouton::draw() const
{
	ShapeEntity::draw();
	GameManager::getInstance()->getWindow()->draw(*BoutonText);
}
