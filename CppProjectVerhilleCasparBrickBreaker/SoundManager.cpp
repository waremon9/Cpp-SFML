#include "SoundManager.h"
#include <iostream>

SoundManager* SoundManager::Instance = nullptr;

SoundManager::SoundManager()
{
	AllSounds.resize(SoundLabel::Count);

	getSoundFromFile(SoundLabel::Piou, "Piou.wav");
	getSoundFromFile(SoundLabel::Toc, "Toc.wav");
	getSoundFromFile(SoundLabel::Boom, "Boom.wav");
	getSoundFromFile(SoundLabel::RerunOst, "RerunOst.wav");
}

void SoundManager::getSoundFromFile(int i, const char* str)
{
	sf::SoundBuffer* b = new sf::SoundBuffer;
	b->loadFromFile(str);

	sf::Sound* s = new sf::Sound();
	s->setBuffer(*b);
	AllSounds[i] = s;
}

SoundManager* SoundManager::getInstance()
{
	if (Instance == nullptr) {
		Instance = new SoundManager();
	}
	return Instance;
}

void SoundManager::playSound(SoundLabel s)
{
	AllSounds[s]->play();
}
