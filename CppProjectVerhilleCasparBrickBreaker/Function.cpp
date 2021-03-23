#define _USE_MATH_DEFINES
#include "Function.h"
#include <random>
#include <SFML/Graphics.hpp>

//return random int between min(include) and max(include)
int RandomInt(int min, int max) {
    return rand() % (max - min + 1) + min;
}

//convert degree to radian
float convertToRadian(float degree) {
    return (degree * (M_PI / 180));
}

//normalize a vector2
sf::Vector2<float> normalizeVector(sf::Vector2<float> vect) {
    float mag = sqrt(vect.x * vect.x + vect.y * vect.y);
    return vect / mag;
}

//get the surface normal of a segment (from left to right)
sf::Vector2<float> getNormalVector(sf::Vector2<float> segStart, sf::Vector2<float> segEnd) {
    sf::Vector2<float> normal{ -(segEnd.y - segStart.y), (segEnd.x - segStart.x) };
    return normalizeVector(normal);
}

//return the dot product of 2 vector2
float dotProduct(sf::Vector2<float> vect1, sf::Vector2<float> vect2) {
    return vect1.x * vect2.x + vect1.y * vect2.y;
}

//return the distance between 2 points
float distance2Points(sf::Vector2<float> p1, sf::Vector2<float> p2) {
    return abs(sqrt((p2.x - p1.x)* (p2.x - p1.x) + (p2.y - p1.y) * (p2.y - p1.y)));
}

#include <algorithm>

bool vectorContain(std::vector<Entity*> v, Entity* elem) {
    if (std::find(v.begin(), v.end(), elem) != v.end()) {
        return true;
    }
    return false;
}
