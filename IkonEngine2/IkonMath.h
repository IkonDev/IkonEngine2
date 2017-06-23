#pragma once
#include <SFML/Graphics.hpp>
static class IkonMath
{
public:
	static float Length(const sf::Vector2f& Vec);
	static sf::Vector2f Normalize(const sf::Vector2f& Vec);
};

