#include "UIManager.h"
#include "ScorePanel.h"
#include "GameManager.h"
#include "RessourceManager.h"

UIManager* UIManager::Instance = nullptr;

UIManager::UIManager() {
	GameManager* GM = GameManager::getInstance();

	Score = 0;
	_ScorePanel = new ScorePanel(sf::Vector2f(0, GM->getWindow()->getSize().y - 70));

	for (int i = 0; i < GM->getMaxBall(); i++) {
		sf::Sprite* s = new sf::Sprite;
		s->setTexture(*RessourceManager::getInstance()->getTexture(RessourceManager::Ball));
		s->setPosition(sf::Vector2f(GM->getWindow()->getSize().x - 40 - 40 * i,GM->getWindow()->getSize().y - 40));
		BallSprites.push_back(s);
	}
}

UIManager* UIManager::getInstance()
{
	if (Instance == nullptr) {
		Instance = new UIManager();
	}
	return Instance;
}

void UIManager::drawUI()
{
	GameManager* GM = GameManager::getInstance();

	_ScorePanel->draw();

	for (int i = 0; i < GM->getMaxBall() - GM->getAllBalls().size(); i++) {
		GM->getWindow()->draw(*BallSprites[i]);
	}
}


void UIManager::addScore(int s) {
	Score += s;
	_ScorePanel->updateScore(Score);
}