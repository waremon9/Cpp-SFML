#pragma once
#include <SFML/Graphics.hpp>

int RandomInt(int min, int max);
float convertToRadian(float degree);
sf::Vector2<float> normalizeVector(sf::Vector2<float> vect);
sf::Vector2<float> getNormalVector(sf::Vector2<float> segStart, sf::Vector2<float> segEnd);
float dotProduct(sf::Vector2<float> vect1, sf::Vector2<float> vect2);