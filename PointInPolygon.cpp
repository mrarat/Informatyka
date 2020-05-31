#include <iostream>
#include <string>
#include <cmath>
#include <vector>

template<class T>
struct Vec2
{
	T x;
	T y;

	Vec2(): x(0), y(0) {}
	Vec2(T _x, T _y): x(_x), y(_y) {}

	inline bool operator == (const Vec2<T>& obj) const
	{
		return (x == obj.x && y == obj.y);
	}
};

typedef Vec2<unsigned int> Vec2u;
typedef Vec2<int>          Vec2i;
typedef Vec2<float>        Vec2f;
typedef Vec2<double>       Vec2d;

bool IsInPolygon(const Vec2d& p, const std::vector<Vec2d>& v) // p - point, v - polygon
{
	/* Note: The algorithm may give a bad result if there are consecutive segments on the ray.
		You can fix this by simplifying the polygon before passing it to this function.
		To simplify the polygon, convert all consecutive segments lying on the ray into two segments
		- one is the edge and the other is a separate figure to check.
	*/

	unsigned int count = 0; // number of intersections with ray with initial point 'p'  

	const Vec2d* first;
	const Vec2d* second;

	for (int i = 0; i < v.size(); i++)
	{
		first = &v[i];
		second = &v[(i + 1) % v.size()];

		if (p == *first) // 'p' lies on 'first' 
			return true;

		if (first->y == p.y && second->y == p.y) // segment lies on line y = p.y
		{
			if (first->x > p.x && second->x > p.x) // segment lies on ray
			{
				if ((v[(i - 1) % v.size()].y > p.y) != (v[(i + 2) % v.size()].y > p.y)) // previous and next segments lie on different sides of ray
					count++;

				i++;
				continue;
			}
			else if (first->x < p.x && second->x < p.x) // segment does not intersect ray
				continue;
			else // 'p' lies on segment
				return true;
		}

		double fy = first->y - p.y;
		double sy = second->y - p.y;
		
		if (std::signbit(fy) == std::signbit(sy) || second->y == p.y) // segment does not intersect line or it should not be processed right now
			continue;

		if (first->y == p.y)
		{
			if ((second->y > p.y) != (v[(i - 1) % v.size()].y > p.y))
				count++;
			continue;
		}

		// segment intersects line
		double x = (abs(fy) * second->x + abs(sy) * first->x) / (abs(fy) + abs(sy)); // point of intersection

		if (x == p.x) // 'p' lies on segment 
			return true;

		if (x > p.x) // segment intersects ray
			count++;
	}

	return count % 2;
}

int main()
{
	std::ios_base::sync_with_stdio(0); std::cin.tie(0);

	unsigned int points; std::cin >> points;
	std::vector<Vec2d> v(points, Vec2d());
	for (Vec2d& e : v)
		std::cin >> e.x >> e.y;

	Vec2d p; std::cin >> p.x >> p.y;

	if (IsInPolygon(p, v))
		std::cout << "TAK\n";
	else
		std::cout << "NIE\n";

	return 0;
}
