#pragma once
#include "ConvexHull.h"
struct Piece;
class SquareTypes
{
public:
	static ConvexHull GetSquare(Piece& TargetPiece, const sf::Vector2f& Pos, const sf::Vector2f& Size);
};