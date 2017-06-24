#include "BaseApplication.h"

BaseApplication::BaseApplication()
{
	WindowWidth = 800;
	WindowHeight = 600;
	WindowTitle = "Application - B++ Entertainment";
	AntiAliasingLevel = 8;
	WindowSettings.antialiasingLevel = AntiAliasingLevel;
	MainWindow = new sf::RenderWindow(sf::VideoMode(WindowWidth, WindowHeight), WindowTitle, sf::Style::Default, WindowSettings);

}

BaseApplication::BaseApplication(unsigned int a_WindowWidth, unsigned int a_WindowHeight, const char * a_WindowTitle, unsigned int a_AALevel)
{
	WindowWidth = a_WindowWidth;
	WindowHeight = a_WindowHeight;
	WindowTitle = a_WindowTitle;
	AntiAliasingLevel = a_AALevel;
	WindowSettings.antialiasingLevel = AntiAliasingLevel;
	MainWindow = new sf::RenderWindow(sf::VideoMode(WindowWidth, WindowHeight), WindowTitle, sf::Style::Default, WindowSettings);
}

BaseApplication::~BaseApplication()
{
	if( MainWindow != nullptr)
	{
		delete MainWindow;
		MainWindow = nullptr;
	}
}

void BaseApplication::Startup()
{
	L = Landscape(30,10);
}

void BaseApplication::Run()
{
	Startup();
	while (MainWindow->isOpen())
	{
		sf::Event event;
		while (MainWindow->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				MainWindow->close();
			if (event.type == sf::Event::MouseMoved)
			{
				
			}
		}
		Update();
		Draw();
	}
}

void BaseApplication::Update()
{

}

void BaseApplication::Draw()
{
	MainWindow->clear(sf::Color::White);
	L.Draw(*MainWindow);

	MainWindow->display();
}
