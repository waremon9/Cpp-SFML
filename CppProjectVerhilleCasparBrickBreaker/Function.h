#pragma once
#include <SFML/Graphics.hpp>

int RandomInt(int, int);
float convertToRadian(float);
sf::Vector2<float> normalizeVector(sf::Vector2<float>);
sf::Vector2<float> getNormalVector(sf::Vector2<float>, sf::Vector2<float>);
float dotProduct(sf::Vector2<float>, sf::Vector2<float>);
float distance2Points(sf::Vector2<float>, sf::Vector2<float>);