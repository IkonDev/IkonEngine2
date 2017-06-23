#include "SquareTypes.h"
#include "MarchingSquares.h"

ConvexHull SquareTypes::GetSquare(Piece& TargetPiece, const sf::Vector2f& Pos, const sf::Vector2f& Size)
{
	Piece PieceToGet = TargetPiece;
	ConvexHull tempHull;
	std::vector<sf::Vector2f> tempPoints;
	unsigned int Value = PieceToGet.GetIntType();

	float ScaledSizeY = Size.y / 2.0f;
	float ScaledSizeX = Size.x / 2.0f;
	
	switch (Value)
	{
	case 0:
		//Empty hull, no need to create a hull
		break;
	case 1:
		tempPoints.push_back(sf::Vector2f(Pos.x + ScaledSizeX, Pos.y + ScaledSizeY));
		tempPoints.push_back(sf::Vector2f(Pos.x + ScaledSizeX, Pos.y));
		tempPoints.push_back(sf::Vector2f(Pos.x, Pos.y + ScaledSizeY));
		break;
	case 2:
		tempPoints.push_back(sf::Vector2f(Pos.x - ScaledSizeX, Pos.y + ScaledSizeY));
		tempPoints.push_back(sf::Vector2f(Pos.x - ScaledSizeX, Pos.y));
		tempPoints.push_back(sf::Vector2f(Pos.x, Pos.y + ScaledSizeY));
		break;
	case 3:
		tempPoints.push_back(sf::Vector2f(Pos.x - ScaledSizeX, Pos.y + ScaledSizeY));
		tempPoints.push_back(sf::Vector2f(Pos.x + ScaledSizeX, Pos.y));
		tempPoints.push_back(sf::Vector2f(Pos.x - ScaledSizeX, Pos.y));
		tempPoints.push_back(sf::Vector2f(Pos.x + ScaledSizeX, Pos.y + ScaledSizeY));
		break;
	case 4:
		tempPoints.push_back(sf::Vector2f(Pos.x + ScaledSizeX, Pos.y - ScaledSizeY));
		tempPoints.push_back(sf::Vector2f(Pos.x + ScaledSizeX, Pos.y));
		tempPoints.push_back(sf::Vector2f(Pos.x, Pos.y - ScaledSizeY));
		break;
	case 5:
		tempPoints.push_back(sf::Vector2f(Pos.x, Pos.y - ScaledSizeY));
		tempPoints.push_back(sf::Vector2f(Pos.x + ScaledSizeX, Pos.y - ScaledSizeY));
		tempPoints.push_back(sf::Vector2f(Pos.x, Pos.y + ScaledSizeY));
		tempPoints.push_back(sf::Vector2f(Pos.x + ScaledSizeX, Pos.y + ScaledSizeY));
		break;
	case 6:
		tempPoints.push_back(sf::Vector2f(Pos.x - ScaledSizeX, Pos.y));
		tempPoints.push_back(sf::Vector2f(Pos.x, Pos.y - ScaledSizeY));
		tempPoints.push_back(sf::Vector2f(Pos.x + ScaledSizeX, Pos.y - ScaledSizeY));
		tempPoints.push_back(sf::Vector2f(Pos.x - ScaledSizeX, Pos.y + ScaledSizeY));
		tempPoints.push_back(sf::Vector2f(Pos.x + ScaledSizeX, Pos.y));
		tempPoints.push_back(sf::Vector2f(Pos.x, Pos.y + ScaledSizeY));
		break;
	case 7:
		tempPoints.push_back(sf::Vector2f(Pos.x - ScaledSizeX, Pos.y));
		tempPoints.push_back(sf::Vector2f(Pos.x, Pos.y - ScaledSizeY));
		tempPoints.push_back(sf::Vector2f(Pos.x + ScaledSizeX, Pos.y - ScaledSizeY));
		tempPoints.push_back(sf::Vector2f(Pos.x - ScaledSizeX, Pos.y + ScaledSizeY));
		tempPoints.push_back(sf::Vector2f(Pos.x + ScaledSizeX, Pos.y + ScaledSizeY));
		break;
	case 8:
		tempPoints.push_back(sf::Vector2f(Pos.x - ScaledSizeX, Pos.y - ScaledSizeY));
		tempPoints.push_back(sf::Vector2f(Pos.x - ScaledSizeX, Pos.y));
		tempPoints.push_back(sf::Vector2f(Pos.x, Pos.y - ScaledSizeY));
		break;
	case 9:
		tempPoints.push_back(sf::Vector2f(Pos.x - ScaledSizeX, Pos.y));
		tempPoints.push_back(sf::Vector2f(Pos.x, Pos.y - ScaledSizeY));
		tempPoints.push_back(sf::Vector2f(Pos.x - ScaledSizeX, Pos.y - ScaledSizeY));
		tempPoints.push_back(sf::Vector2f(Pos.x + ScaledSizeX, Pos.y + ScaledSizeY));
		tempPoints.push_back(sf::Vector2f(Pos.x, Pos.y + ScaledSizeY));
		tempPoints.push_back(sf::Vector2f(Pos.x + ScaledSizeX, Pos.y));
		break;
	case 10:
		tempPoints.push_back(sf::Vector2f(Pos.x - ScaledSizeX, Pos.y - ScaledSizeY));
		tempPoints.push_back(sf::Vector2f(Pos.x, Pos.y - ScaledSizeY));
		tempPoints.push_back(sf::Vector2f(Pos.x - ScaledSizeX, Pos.y + ScaledSizeY));
		tempPoints.push_back(sf::Vector2f(Pos.x, Pos.y + ScaledSizeY));
		break;
	case 11:
		tempPoints.push_back(sf::Vector2f(Pos.x - ScaledSizeX, Pos.y - ScaledSizeY));
		tempPoints.push_back(sf::Vector2f(Pos.x + ScaledSizeX, Pos.y + ScaledSizeY));
		tempPoints.push_back(sf::Vector2f(Pos.x - ScaledSizeX, Pos.y + ScaledSizeY));
		tempPoints.push_back(sf::Vector2f(Pos.x, Pos.y - ScaledSizeY));
		tempPoints.push_back(sf::Vector2f(Pos.x + ScaledSizeX, Pos.y));
		break;
	case 12:
		tempPoints.push_back(sf::Vector2f(Pos.x - ScaledSizeX, Pos.y));
		tempPoints.push_back(sf::Vector2f(Pos.x + ScaledSizeX, Pos.y));
		tempPoints.push_back(sf::Vector2f(Pos.x - ScaledSizeX, Pos.y - ScaledSizeY));
		tempPoints.push_back(sf::Vector2f(Pos.x + ScaledSizeX, Pos.y - ScaledSizeY));
		break;
	case 13:
		tempPoints.push_back(sf::Vector2f(Pos.x - ScaledSizeX, Pos.y - ScaledSizeY));
		tempPoints.push_back(sf::Vector2f(Pos.x + ScaledSizeX, Pos.y - ScaledSizeY));
		tempPoints.push_back(sf::Vector2f(Pos.x + ScaledSizeX, Pos.y + ScaledSizeY));
		tempPoints.push_back(sf::Vector2f(Pos.x - ScaledSizeX, Pos.y));
		tempPoints.push_back(sf::Vector2f(Pos.x, Pos.y + ScaledSizeY));
		break;
	case 14:
		tempPoints.push_back(sf::Vector2f(Pos.x - ScaledSizeX, Pos.y - ScaledSizeY));
		tempPoints.push_back(sf::Vector2f(Pos.x + ScaledSizeX, Pos.y - ScaledSizeY));
		tempPoints.push_back(sf::Vector2f(Pos.x - ScaledSizeX, Pos.y + ScaledSizeY));
		tempPoints.push_back(sf::Vector2f(Pos.x + ScaledSizeX, Pos.y));
		tempPoints.push_back(sf::Vector2f(Pos.x, Pos.y + ScaledSizeY));
		break;
	case 15:
		tempPoints.push_back(sf::Vector2f(Pos.x - ScaledSizeX, Pos.y - ScaledSizeY));
		tempPoints.push_back(sf::Vector2f(Pos.x + ScaledSizeX, Pos.y - ScaledSizeY));
		tempPoints.push_back(sf::Vector2f(Pos.x - ScaledSizeX, Pos.y + ScaledSizeY));
		tempPoints.push_back(sf::Vector2f(Pos.x + ScaledSizeX, Pos.y + ScaledSizeY));
		break;
	}


	tempHull.SetPoints(tempPoints);
	tempHull.CreateHull();

	return tempHull;
}