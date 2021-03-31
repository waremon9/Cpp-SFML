#include "UIManager.h"
#include "ScorePanel.h"
#include "GameManager.h"

UIManager* UIManager::Instance = nullptr;

UIManager::UIManager() {
	Score = 0;
	_ScorePanel = new ScorePanel(sf::Vector2f(0, GameManager::getInstance()->getWindow()->getSize().y - 70));
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
	_ScorePanel->draw();
}


void UIManager::addScore(int s) {
	Score += s;
	_ScorePanel->updateScore(Score);
}