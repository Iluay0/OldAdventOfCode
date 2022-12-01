#include "../../Utils/Utils.h"
#include "Part2.h"

struct Point
{
	int x;
	int y;
	int encounters;

	Point()
	{
		x = -1;
		y = -1;
		encounters = 0;
	}
};

// #define __POINTS_TEST
#ifdef __POINTS_TEST
#define POINT_AMOUNT 10
#else
#define POINT_AMOUNT 1000
#endif

extern Point* GetPoint(std::vector<Point>& points, int x, int y);
void Part2::Run(std::list<std::string> inputs)
{
	std::vector<Point> points;
	for (int x = 0; x < POINT_AMOUNT; x++)
	{
		for (int y = 0; y < POINT_AMOUNT; y++)
		{
			Point point;
			point.x = x;
			point.y = y;
			point.encounters = 0;
			points.push_back(point);
		}
	}

	int i = 1;
	for (auto& it : inputs)
	{
		std::cout << "Move " << i << " out of " << inputs.size() << "...\n";
		auto coordinates = Utils::split(it, ' ');

		Point startCoords;
		startCoords.y = stoi(Utils::split(coordinates[0], ',')[0]);
		startCoords.x = stoi(Utils::split(coordinates[0], ',')[1]);

		Point endCoords;
		endCoords.y = stoi(Utils::split(coordinates[2], ',')[0]);
		endCoords.x = stoi(Utils::split(coordinates[2], ',')[1]);

		if (startCoords.x == endCoords.x)
		{
			int y = startCoords.y;
			while (true)
			{
				Point* pPoint = GetPoint(points, startCoords.x, y);
				if (!pPoint)
					throw;
				pPoint->encounters++;

				if (y == endCoords.y)
					break;

				if (y <= endCoords.y)
					y++;
				else
					y--;
			}
		}
		else if (startCoords.y == endCoords.y)
		{
			int x = startCoords.x;
			while (true)
			{
				Point* pPoint = GetPoint(points, x, startCoords.y);
				if (!pPoint)
					throw;
				pPoint->encounters++;

				if (x == endCoords.x)
					break;

				if (x <= endCoords.x)
					x++;
				else
					x--;
			}
		}
		else
		{
			int x = startCoords.x;
			int y = startCoords.y;
			while (true)
			{
				Point* pPoint = GetPoint(points, x, y);
				if (!pPoint)
					throw;
				pPoint->encounters++;

				if (x == endCoords.x && y == endCoords.y)
					break;

				if (x <= endCoords.x)
					x++;
				else
					x--;

				if (y <= endCoords.y)
					y++;
				else
					y--;
			}
		}
		i++;
	}

#ifdef __POINTS_TEST
	int x = -1;
	for (auto& it : points)
	{
		if (x != it.x)
		{
			x = it.x;
			std::cout << "\n";
		}
		std::cout << it.encounters;
	}
#endif

	int count = 0;
	for (auto& it : points)
	{
		if (it.encounters >= 2)
			count++;
	}
	std::cout << "\nResult: " << count;
}