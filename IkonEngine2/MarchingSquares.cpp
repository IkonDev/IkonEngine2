#include "MarchingSquares.h"
#include "ConvexHull.h"
#include "SquareTypes.h"
#include "Landscape.h"
#include <iostream>
//#include "Input.h"

MarchingSquares::MarchingSquares()
{
}


MarchingSquares::~MarchingSquares()
{
}

void MarchingSquares::Create(std::string Name, MapArray Map, bool FillType)
{
	m_MapName = Name;

	m_Width = Map.GetWidth() - 1;
	m_Height = Map.GetHeight() - 1;

	int X = m_Width;
	int Y = m_Height;

	//Declare
	Piece** TempMap = new Piece*[X];

	//Allocate
	for (int i = 0; i < X; ++i)
	{
		TempMap[i] = new Piece[Y];
	}

	//Initialize

	Piece Temp = Piece();
	Temp.TL = FillType;
	Temp.BL = FillType;
	Temp.TR = FillType;
	Temp.BR = FillType;

	//Assign Empty structs
	for (int y = 0; y < Y; ++y)
	{
		for (int x = 0; x < X; ++x)
		{
			TempMap[x][y] = Temp;
		}
	}

	//Assign
	m_PieceMap = TempMap;

	//for (int i = 0; i < X; ++i)
	//{
	//	delete TempMap[i];
	//	TempMap[i] = nullptr;
	//}
	//delete TempMap;
	//TempMap = nullptr;
}

void MarchingSquares::MarchSquares(MapArray Map, int ScreenHeight, int TileSize)
{
	auto TempMap = Map.GetMap();

	for (int y = 0; y < m_Height; ++y)
	{
		for (int x = 0; x < m_Width; ++x)
		{
			Piece T = Piece();
			T.TL = TempMap[x][y];
			T.TR = TempMap[x + 1][y];
			T.BL = TempMap[x][y + 1];
			T.BR = TempMap[x + 1][y + 1];

			m_PieceMap[x][y] = T;
		}
	}

	//Accumulate Hulls
	for (int y = 0; y < m_Height; ++y)
	{
		for (int x = 0; x < m_Width; ++x)
		{
			ConvexHull T = ConvexHull();

			T = SquareTypes::GetSquare(m_PieceMap[x][y],
				sf::Vector2f(x * TileSize + (TileSize / 2), 
							 y * TileSize + (TileSize / 2)), //POS
				sf::Vector2f(TileSize, TileSize));														   //SIZE

			m_Hulls.push_back(T);
		}
	}
}

void MarchingSquares::PrintMap()
{
	for (int y = 0; y < m_Height; ++y)
	{
		for (int x = 0; x < m_Width; ++x)
		{
			std::cout << m_PieceMap[x][y].TL;
			std::cout << m_PieceMap[x][y].TR;
			std::cout << m_PieceMap[x][y].BL;
			std::cout << m_PieceMap[x][y].BR;
			std::cout << "|";
		}
		std::cout << std::endl;
	}
	std::cout << m_MapName << std::endl;
}

void MarchingSquares::DrawMap(sf::RenderWindow& Window)
{
	//NOTE: Need to change this so that all the hulls are created and stored. So shadows can be drawn before objects
	int mX = /*MouseX*/32;
	int mY = 32/* MouseY*/;

	//Render Hull Shadows First
	for each(ConvexHull C in m_Hulls)
	{
		ConvexHull S = C.CreateShadowHull(C, sf::Vector2f(mX, mY));
		S.DrawHull(sf::Vector3f(20, 20, 25), 1, Window);
	}
	for each(ConvexHull C in m_Hulls)
	{
		C.DrawHull(sf::Vector3f(0.1f, 0.1f, 0.1f), 1.0f, Window);
	}
}

unsigned int Piece::GetIntType()
{
	unsigned int Result = 0;
	Result += this->TL;
	Result = Result << 1;
	Result += this->TR;
	Result = Result << 1;
	Result += this->BL;
	Result = Result << 1;
	Result += this->BR;

	return Result;
}
