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
		return Vec / Length;;
	}
	return sf::Vector2f(0,0);
}
