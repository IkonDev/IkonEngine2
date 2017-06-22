#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class MapArray
{
public:
	MapArray();
	~MapArray();

	void Create(std::string Name, const unsigned int X, const unsigned int Y, bool FillType = false);

	void PrintMap();

	unsigned int** GetMap() const { return m_Map; }
	void SetMap(unsigned int** Map) { m_Map = Map; }

	unsigned int GetWidth() const { return m_Width; }
	unsigned int GetHeight() const { return m_Height; }

	unsigned int& operator() (int x, int y);
private:
	unsigned int** m_Map;
	std::string m_MapName;
	unsigned int m_Width;
	unsigned int m_Height;
};

class CellularAutomata
{
public:
	enum Ruleset
	{
		Rule_B678_S345678,
		Rule_B5678_S5678
	};

	static MapArray RandomFill(MapArray InitialMap, unsigned int Seed);
	static MapArray CellularAutomataProcess(MapArray InitialMap, Ruleset Rule, unsigned int Iterations);
	static unsigned int Random();
	static int GetWalls(MapArray InitialMap, int x, int y, int Scope);
};

class Landscape
{
public:
	Landscape();
	Landscape(unsigned int X, unsigned int Y);
	~Landscape();
	void Draw(sf::RenderWindow& Window);

private:
	unsigned int LandscapeWidth;
	unsigned int LandscapeHeight;

	MapArray Map;

	sf::Texture A;
	sf::Texture B;
	sf::Texture C;
};

