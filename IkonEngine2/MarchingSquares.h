#pragma once
#include <SFML/Graphics.hpp>
#include "ConvexHull.h"
#include <vector>
struct Piece
{
	bool TL;
	bool TR;
	bool BL;
	bool BR;
	unsigned int IntType;
	unsigned int GetIntType();
};
class ConvexHull;
class MapArray;
class MarchingSquares
{
public:
	MarchingSquares();
	~MarchingSquares();

	void Create(std::string Name, MapArray Map, bool FillType = false);

	void MarchSquares(MapArray Map, int ScreenHeight, int TileSize);

	void PrintMap();

	void DrawMap(sf::RenderWindow& Window);
private:
	Piece** m_PieceMap;
	std::string m_MapName;
	unsigned int m_Width;
	unsigned int m_Height;
	std::vector<ConvexHull> m_Hulls;
};