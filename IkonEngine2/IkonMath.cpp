#include "IkonMath.h"


float IkonMath::Length(const sf::Vector2f & Vec)
{
	return sqrt((Vec.x * Vec.x) + (Vec.y * Vec.y));
}

sf::Vector2f IkonMath::Normalize(const sf::Vector2f & Vec)
{
	float Length = IkonMath::Length(Vec);
	if (Length > 0)
	{
		float X = Vec.x / Length;
		float Y = Vec.y / Length;

		return sf::Vector2f(X, Y);
	}
	return sf::Vector2f(0,0);
}
