#include "Landscape.h"

#include <random>
#include <ctime>
#include <iostream>

MapArray::MapArray()
{
	m_Map = nullptr;
}

MapArray::~MapArray()
{
	//NOTE: Broken code
	//if (m_Map != nullptr)
	//{
	//	for (int i = 0; i < m_Height; ++i)
	//	{
	//		delete m_Map[i];
	//	}
	//}
}

void MapArray::Create(std::string Name, const unsigned int X, const unsigned int Y, bool FillType)
{
	m_MapName = Name;

	m_Width = X;
	m_Height = Y;

	//Declare
	unsigned int** Map = new unsigned int*[X];

	//Allocate
	for (int i = 0; i < (int)X; ++i)
	{
		Map[i] = new unsigned int[Y];
	}

	//Initialize
	for (int y = 0; y < (int)Y; ++y)
	{
		for (int x = 0; x < (int)X; ++x)
		{
			Map[x][y] = FillType;
		}
	}

	//Assign
	m_Map = Map;
}

void MapArray::PrintMap()
{
	for (int y = 0; y < (int)m_Height; ++y)
	{
		for (int x = 0; x < (int)m_Width; ++x)
		{
			if (m_Map[x][y] == 0)
			{
				std::cout << ".";
			}
			else
			{
				std::cout << "#";
			}
		}
		std::cout << std::endl;
	}
	std::cout << m_MapName << std::endl;
}

unsigned int& MapArray::operator()(int x, int y)
{
	return m_Map[x][y];
}

MapArray CellularAutomata::RandomFill(MapArray InitialMap, unsigned int Seed)
{
	srand(Seed);

	int Width = InitialMap.GetWidth();
	int Height = InitialMap.GetHeight();

	//auto Map = InitialMap.GetMap();

	for (int y = 0; y < Height; ++y)
	{
		for (int x = 0; x < Width; ++x)
		{
			if (x <= 0 || y <= 0)
			{
				InitialMap(x, y) = true;
			}
			else if (x >= Width - 1 || y >= Height - 1)
			{
				InitialMap(x, y) = true;
			}
			else
			{
				InitialMap(x, y) = Random();
			}
		}
	}

	//InitialMap.SetMap(Map);
	return InitialMap;
}

MapArray CellularAutomata::CellularAutomataProcess(MapArray InitialMap, Ruleset Rule, unsigned int Iterations)
{
	int Width = InitialMap.GetWidth();
	int Height = InitialMap.GetHeight();
	for (int i = 0; i < (int)Iterations; ++i)
	{
		for (int y = 0; y < Height; ++y)
		{
			for (int x = 0; x < Width; ++x)
			{
				int Walls = GetWalls(InitialMap, x, y, 1);
				switch (Rule)
				{
				case Rule_B678_S345678:
					if (InitialMap(x, y) == 0)
					{
						if (Walls >= 6 && Walls <= 8)
						{
							InitialMap(x, y) = 1;
						}
					}
					else //InitialMap(x,y) == 1
					{
						if (Walls >= 3 && Walls <= 8)
						{
							InitialMap(x, y) = 1;
						}
						else
						{
							InitialMap(x, y) = 0;
						}
					}
					break;

				case Rule_B5678_S5678:
					if (InitialMap(x, y) == 0)
					{
						if (Walls >= 5 && Walls <= 8)
						{
							InitialMap(x, y) = 1;
						}
					}
					else
					{
						if (Walls >= 5 && Walls <= 8)
						{
							InitialMap(x, y) = 1;
						}
						else
						{
							InitialMap(x, y) = 0;
						}
					}
					break;
				}
			}
		}
	}
	return InitialMap;
}

unsigned int CellularAutomata::Random()
{
	return rand() % 100 < 45 ? 1 : 0;
}

int CellularAutomata::GetWalls(MapArray InitialMap, int x, int y, int Scope)
{
	int Walls = 0;
	int ScopeSize = 1 + (Scope * 2);

	int ScopeWStart = x - Scope;
	int ScopeWidth = ScopeWStart + ScopeSize;

	int ScopeHStart = y - Scope;
	int ScopeHeight = ScopeHStart + ScopeSize;

	for (int Y = ScopeHStart; Y < ScopeHeight; ++Y)
	{
		for (int X = ScopeWStart; X < ScopeWidth; ++X)
		{
			if (X != x || Y != y)
			{
				if (X < 0 || Y < 0)
				{
					Walls++;
				}
				else if (X > (int)InitialMap.GetWidth() - 1 || Y > (int)InitialMap.GetHeight() - 1)
				{
					Walls++;
				}
				else if (InitialMap(X, Y) == 1)
				{
					Walls++;
				}
			}
		}
	}
	return Walls;
}

Landscape::Landscape()
{
	LandscapeWidth = 40;
	LandscapeHeight = 30;
	Startup();
}

Landscape::Landscape(unsigned int X, unsigned int Y)
{
	LandscapeWidth = X;
	LandscapeHeight = Y;
	Startup();
}

Landscape::~Landscape()
{
}

void Landscape::Startup()
{
	Map = MapArray();
	Map.Create("TestMap", LandscapeWidth, LandscapeHeight);
	Map = CellularAutomata::RandomFill(Map, rand());
	Map = CellularAutomata::CellularAutomataProcess(Map, CellularAutomata::Ruleset::Rule_B678_S345678, 2);
	MS = MarchingSquares();
	MS.Create("Squares", Map);
	MS.MarchSquares(Map, 600, 20);

	A.loadFromFile("Data/TileA.png");
	B.loadFromFile("Data/TileB.png");
	C.loadFromFile("Data/TileC.png");
}

void Landscape::Draw(sf::RenderWindow& Window)
{
	for (int y = 0; y < LandscapeHeight; ++y)
	{
		for (int x = 0; x < LandscapeWidth; ++x)
		{
			sf::RectangleShape Tile = sf::RectangleShape(sf::Vector2f(20, 20));
	
			switch (Map(x,y))
			{
			case 0:
				Tile.setTexture(&A);
				break;
			case 1:
				Tile.setTexture(&B);
				break;
			case 2:
				Tile.setTexture(&C);
				break;
			default:
				Tile.setFillColor(sf::Color::Red);
				break;
			}
			sf::Vector2f Pos = sf::Vector2f(x * 20, y * 20);
			Tile.setPosition(Pos);
			Window.draw(Tile);
		}
	}
	MS.DrawMap(Window);
}