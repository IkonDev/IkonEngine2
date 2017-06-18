#include <SFML/Graphics.hpp>

int main()
{
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;
	sf::RenderWindow window(sf::VideoMode(250, 100), "SFML Test!", sf::Style::Default, settings);

	//Create a shape
	sf::ConvexShape convex;
	//Set the point count to 3, and set each of the points.
	convex.setPointCount(3);
	convex.setPoint(0, sf::Vector2f(5, 5));   //TOP
	convex.setPoint(1, sf::Vector2f(245, 95));//BOT LEFT
	convex.setPoint(2, sf::Vector2f(5, 95));  //BOT RIGHT
	convex.setOutlineThickness(0);
	convex.setFillColor(sf::Color::Green);

	sf::ConvexShape convex2;
	convex2.setPointCount(3);
	convex2.setPoint(0, sf::Vector2f(5, 5));   
	convex2.setPoint(1, sf::Vector2f(245, 5)); 
	convex2.setPoint(2, sf::Vector2f(245, 95));
	convex2.setOutlineThickness(0);
	convex2.setFillColor(sf::Color::Magenta);

	//Some boilerplate
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		//Clear the window with a chosen color.
		window.clear(sf::Color::Black);
		//Draw the selected shape
		window.draw(convex);
		window.draw(convex2);
		//Display to window
		window.display();
	}

	return 0;
}