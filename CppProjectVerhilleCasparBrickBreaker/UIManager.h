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

public:
	static UIManager* getInstance();

	void addScore(int x);

	void drawUI();
};

