#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

class ConvexHull
{
public:
	ConvexHull();
	~ConvexHull();

	void SetPoints(const std::vector<sf::Vector2f>& a_points); //Set the mesh verticies
	void AddPoints(const std::vector<sf::Vector2f>& a_points); //Add verticies the mesh
	void CreateHull(); //Giftwrap the mesh and create a convex hull
	static ConvexHull CreateShadowHull(const ConvexHull& Hull, const sf::Vector2f& LightPos);
	void DrawHull(const sf::Vector3f& colour, float Depth, sf::RenderWindow& Window); //Draw the hull using aie::gizmos.

	const std::vector<sf::Vector2f>& GetPoints() const { return m_pointList; }

private:
	std::vector<sf::Vector2f> m_pointList; //List of verts
	sf::Vector2f m_centreAverage; //Centre calculated from average of giftwrapped verticies.

	int Orientation(const sf::Vector2f& p, const sf::Vector2f& q, const sf::Vector2f& r);
};