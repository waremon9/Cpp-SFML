#pragma once
#include <SFML/Graphics.hpp>

class RessourceManager
{
public:
	enum TextureLabel
	{
		Canon,
		Ball,
		ExplosionPart,
		BombIcon,
		CountTexture
	};

	enum FontLabel
	{
		Arial,
		MLFont,
		CountFont
	};

private:

	std::vector<sf::Texture*> AllTexture;
	std::vector<sf::Font*> AllFont;

	static RessourceManager* Instance;
	RessourceManager();

	void getTextureFromFile(int, const char*);
	void getFontFromFile(int, const char*);

public:
	static RessourceManager* getInstance();

	sf::Texture* getTexture(TextureLabel);
	sf::Font* getFont(FontLabel);
};

