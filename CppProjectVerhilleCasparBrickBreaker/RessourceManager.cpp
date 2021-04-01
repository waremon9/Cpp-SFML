#include "RessourceManager.h"

RessourceManager* RessourceManager::Instance = nullptr;

RessourceManager::RessourceManager()
{
	AllTexture.resize(TextureLabel::CountTexture);

	getTextureFromFile(TextureLabel::Canon, "canon.png");
	getTextureFromFile(TextureLabel::Ball, "Ball.png");
	getTextureFromFile(TextureLabel::ExplosionPart, "explosionParticle.png");
	getTextureFromFile(TextureLabel::BombIcon, "BombIcon.png");


	AllFont.resize(FontLabel::CountFont);

	getFontFromFile(FontLabel::Arial, "ARIAL.TTF");
	getFontFromFile(FontLabel::MLFont, "MarioLuigi2.ttf");
}

void RessourceManager::getTextureFromFile(int i, const char* str)
{
	sf::Texture* t = new sf::Texture;
	t->loadFromFile(str);
	t->setSmooth(true);
	AllTexture[i] = t;
}

void RessourceManager::getFontFromFile(int i, const char* str)
{
	sf::Font* t = new sf::Font;
	t->loadFromFile(str);
	AllFont[i] = t;
}

RessourceManager* RessourceManager::getInstance()
{
	if (Instance == nullptr) {
		Instance = new RessourceManager();
	}
	return Instance;
}

sf::Texture* RessourceManager::getTexture(TextureLabel t)
{
	return AllTexture[t];
}

sf::Font* RessourceManager::getFont(FontLabel f)
{
	return AllFont[f];
}
