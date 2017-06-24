#pragma once
#include <SFML/Graphics.hpp>
#include "Landscape.h"
//Base application that comes with a window
class BaseApplication
{
public:
	BaseApplication();
	BaseApplication(unsigned int a_WindowWidth, unsigned int a_WindowHeight, const char* a_WindowTitle, unsigned int a_AALevel = 8);
	~BaseApplication();

	void Startup();
	void Shutdown();
	void Run();
	void Update();
	void Draw();

private:
	sf::ContextSettings WindowSettings;
	sf::RenderWindow* MainWindow = nullptr;
	unsigned int AntiAliasingLevel = 0;
	unsigned int WindowHeight;
	unsigned int WindowWidth;
	const char*  WindowTitle;

	sf::Vector2f Position;
	sf::CircleShape Circ;
	bool upd = false;
	Landscape L;

	sf::Vector2f MouseCoords;
};

