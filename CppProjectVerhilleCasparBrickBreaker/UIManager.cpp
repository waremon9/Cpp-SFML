#include "UIManager.h"
#include "ScorePanel.h"
#include "GameManager.h"
#include "RessourceManager.h"

UIManager* UIManager::Instance = nullptr;

UIManager::UIManager() {
	GameManager* GM = GameManager::getInstance();

	Score = 0;
	_ScorePanel = new ScorePanel(sf::Vector2f(0, GM->getWindow()->getSize().y - 70));

	Offset = 40;
	MaxBallBeforeDisplaySwitch = 8;

	BallSprites.resize(MaxBallBeforeDisplaySwitch);

	for (int i = 0; i < MaxBallBeforeDisplaySwitch; i++) {
		sf::Sprite* s = new sf::Sprite;
		s->setTexture(*RessourceManager::getInstance()->getTexture(RessourceManager::Ball));
		s->setPosition(sf::Vector2f(GM->getWindow()->getSize().x - Offset * (i + 1),GM->getWindow()->getSize().y - Offset));
		BallSprites[i] = s;
	}

	BallQteText = new sf::Text;
	BallQteText->setFont(*RessourceManager::getInstance()->getFont(RessourceManager::MLFont));
	BallQteText->setPosition(sf::Vector2f(GM->getWindow()->getSize().x - Offset * 2.7, GM->getWindow()->getSize().y - Offset * 1.1));
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

	if (GM->getBallAmount() <= MaxBallBeforeDisplaySwitch) {
		for (int i = 0; i < GM->getBallAmount(); i++) {
			GM->getWindow()->draw(*BallSprites[i]);
		}
	}
	else {
		BallQteText->setString(std::to_string(GM->getBallAmount()) + " X");
		GM->getWindow()->draw(*BallSprites[0]);
		GM->getWindow()->draw(*BallQteText);
	}
}

void UIManager::ScoreReset()
{
	Score = 0;
	_ScorePanel->updateScore(Score);
}


void UIManager::addScore(int s) {
	Score += s;
	_ScorePanel->updateScore(Score);
}
