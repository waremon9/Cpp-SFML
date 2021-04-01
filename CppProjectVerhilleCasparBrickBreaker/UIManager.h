#pragma once
#include <SFML/Graphics.hpp>

class ScorePanel;

class UIManager
{
private:
	static UIManager* Instance;
	UIManager();

	float Score;
	ScorePanel* _ScorePanel;

	std::vector<sf::Sprite*> BallSprites;
	int Offset;
	int MaxBallBeforeDisplaySwitch;
	sf::Text* BallQteText;

public:
	static UIManager* getInstance();

	void addScore(int x);

	void drawUI();

	void ScoreReset();
};

