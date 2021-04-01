#pragma once
#include <vector>
#include <SFML/Graphics.hpp>

class Brick;

class NomMarrantTableauUneDimension
{
private	:
	std::vector<Brick*> Tableau;
	int Width;
	int Height;

public:
	NomMarrantTableauUneDimension(int w, int h) { Width = w; Height = h; }

	void pushBack(Brick* b) { Tableau.push_back(b); }
	void setBrickAt(Brick* b, int x, int y) { Tableau[y * Width + x] = b; }
	void setBrickAt(Brick* b, sf::Vector2i taille) { Tableau[taille.y * Width + taille.x] = b; }

	int getWidth() { return Width; }
	int getHeight() { return Height; }

	Brick* getBrickAt(sf::Vector2i taille) { return Tableau[taille.y * Width + taille.x]; }
	Brick* getBrickAt(int x, int y) { return Tableau[y * Width + x]; }

	void clear();
};

