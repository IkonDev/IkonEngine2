#include "ConvexHull.h"
#include "IkonMath.h"
#include <iostream>

ConvexHull::ConvexHull()
{
}


ConvexHull::~ConvexHull()
{
}

void ConvexHull::SetPoints(const std::vector<sf::Vector2f>& a_points)
{
	m_pointList = a_points;
}

void ConvexHull::AddPoints(const std::vector<sf::Vector2f>& a_points)
{
	m_pointList.insert(std::end(m_pointList), std::begin(a_points), std::end(a_points));
}

void ConvexHull::CreateHull()
{
	const int N = m_pointList.size();
	// There must be at least 3 points
	if (N < 3) return;

	// Initialize Result
	std::vector<sf::Vector2f>* Hull = new std::vector<sf::Vector2f>();

	// Find the leftmost point
	int L = 0;

	for (int i = 1; i < N; i++)
	{
		if (m_pointList[i].x < m_pointList[L].x)
		{
			L = i;
		}
	}

	// Start from leftmost point, keep moving counterclockwise
	// until reach the start point again.  This loop runs O(n)
	// times where n is number of points in result or output.
	int P = L, Q;
	int It = 0;
	do
	{
		if (It > N)
		{
			break;
		}
		// Add current point to result
		Hull->push_back(m_pointList[P]);

		// Search for a point 'q' such that orientation(p, x,
		// q) is counterclockwise for all m_pointList 'x'. The idea
		// is to keep track of last visited most counterclock-
		// wise point in q. If any point 'i' is more counterclock-
		// wise than q, then update q.
		Q = (P + 1) % N;

		for (int i = 0; i < N; i++)
		{
			// If i is more counterclockwise than current q, then
			// update q
			int Result = Orientation(m_pointList[P], m_pointList[i], m_pointList[Q]);
			if (Result == 2)
			{
				Q = i;
			}
			else if (Result == 0)
			{
				sf::Vector2f pVec = m_pointList[P];
				sf::Vector2f iVec = m_pointList[i];
				sf::Vector2f qVec = m_pointList[Q];
				if (IkonMath::Length(iVec - pVec) < IkonMath::Length(qVec - pVec))
				{
					Q = Q;
				}
				else
				{
					Q = i;
				}
			}
		}

		// Now q is the most counterclockwise with respect to p
		// Set p as q for next iteration, so that q is added to
		// result 'Hull'
		P = Q;

		//std::cout << P << "|";
		//std::cout << L << std::endl;
		It++;
	} while (P != L);  // While we don't come to first point

					   //Assign the new hull as the mesh
	m_pointList = *Hull;
	delete Hull;
	Hull = nullptr;
	//Find the average of all points and make that the centre.
	sf::Vector2i Total = sf::Vector2i(0,0);
	for (int i = 0; i < m_pointList.size(); ++i)
	{
		Total += (sf::Vector2i)(m_pointList[i]);
	}
	Total /= (int)(m_pointList.size());
	m_centreAverage = (sf::Vector2f)(Total);
}

ConvexHull ConvexHull::CreateShadowHull(const ConvexHull& Hull, const sf::Vector2f& LightPos)
{
	//Create a light length
	float LightLength = 2000.0f;

	//Get the objects verticies
	std::vector<sf::Vector2f> ObjPoints = Hull.GetPoints();
	unsigned int PointAmount = ObjPoints.size();

	//Create a list to store the shadows points
	std::vector<sf::Vector2f> ShadowPoints;

	for (int i = 0; i < PointAmount; ++i)
	{
		//Get a vector from the point to the light
		sf::Vector2f LightToPoint = LightPos - ObjPoints[i];
		float Distance = IkonMath::Length(LightToPoint);
		if (Distance < 1250.0f)
		{
			//Normalize it, to get a unit vector toward the light
			sf::Vector2f Direction = IkonMath::Normalize(LightToPoint);
			//Reverse it, so it points away from the light
			Direction *= -1.0f;
			sf::Vector2f ShadowPoint = ObjPoints[i] + (Direction * LightLength);

			ShadowPoints.push_back(ShadowPoint);
		}

	}
	if (ShadowPoints.size() > 0)
	{
		//Make a new hull and give it all the points of the current hull
		ConvexHull m_ShadowHull = ConvexHull(Hull);
		m_ShadowHull.AddPoints(ShadowPoints);
		m_ShadowHull.CreateHull();
		return m_ShadowHull;
	}
	else
	{
		return ConvexHull();
	}

}

void ConvexHull::DrawHull(const sf::Vector3f& colour, float Depth, sf::RenderWindow& Window)
{
	sf::ConvexShape Shape = sf::ConvexShape(this->GetPoints().size());
	for (int i = 0; i < GetPoints().size(); ++i)
	{
		Shape.setPoint(i, this->GetPoints()[i]);
	}
	Shape.setFillColor(sf::Color(colour.x, colour.y, colour.z));
	//Shape.setPosition(this->m_centreAverage / 4.0f);

	Window.draw(Shape);
}

// To find orientation of an ordered triplet (p, q, r).
// The function returns following values
// 0 --> p, q and r are colinear
// 1 --> Clockwise
// 2 --> Counterclockwise
int ConvexHull::Orientation(const sf::Vector2f& p, const sf::Vector2f& q, const sf::Vector2f& r)
{
	int val = (q.y - p.y) * (r.x - q.x)
			- (q.x - p.x) * (r.y - q.y);

	if (val == 0)
	{
		return 0;
	}

	if (val > 0)
	{
		return 1;
	}

	if (val < 0)
	{
		return 2;
	}
}