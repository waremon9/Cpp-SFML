#pragma once
#include <SFML/Audio.hpp>

class SoundManager
{
public:
	enum SoundLabel
	{
		Piou,
		Toc,
		Boom,
		RerunOst,
		Count
	};

private:

	std::vector<sf::Sound*> AllSounds;

	static SoundManager* Instance;
	SoundManager();

	void getSoundFromFile(int, const char*);

public:
	static SoundManager* getInstance();

	void playSound(SoundLabel);

};

