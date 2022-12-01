#include "../../Utils/Utils.h"
#include "Part1.h"

struct HeightPoint
{
	int value;
	bool isLowPoint;

	HeightPoint()
	{
		value = -1;
		isLowPoint = false;
	}
};

bool HasNearbyLowPoint(std::vector<std::vector<HeightPoint>>& heightMap, int x, int y)
{
	int curValue = heightMap[x][y].value;

	if (x > 0 && heightMap[x-1][y].value <= curValue)
		return true;
	if (x+1 < heightMap.size() && heightMap[x+1][y].value <= curValue)
		return true;
	if (y > 0 && heightMap[x][y-1].value <= curValue)
		return true;
	if (y+1 < heightMap[x].size() && heightMap[x][y+1].value <= curValue)
		return true;

	return false;

	/*
	for (int x2 = x - 1; x2 <= x + 1; x2++)
	{
		for (int y2 = y - 1; y2 <= y + 1; y2++)
		{
			if (x2 != x && y2 != y
				&& x2 >= 0 && y2 >= 0
				&& x2 < heightMap.size() && y2 < heightMap[x2].size())
			{
				int compValue = heightMap[x2][y2].value;
				if (compValue < curValue)
					return false;
			}
		}
	}
	*/
}

void Part1::Run(std::list<std::string> inputs)
{
	std::vector<std::vector<HeightPoint>> heightMap;
	for (auto& it : inputs)
	{
		std::vector<HeightPoint> heightLine;
		for (auto& it2 : it)
		{
			HeightPoint point;
			point.value = it2 - '0';
			point.isLowPoint = false;
			heightLine.push_back(point);
		}
		heightMap.push_back(heightLine);
	}

	for (int x = 0; x < heightMap.size(); x++)
	{
		for (int y = 0; y < heightMap[x].size(); y++)
		{
			if (!HasNearbyLowPoint(heightMap, x, y))
				heightMap[x][y].isLowPoint = true;
		}
	}

	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	int total = 0;
	for (auto& it : heightMap)
	{
		for (auto& it2 : it)
		{
			if (it2.isLowPoint)
			{
				SetConsoleTextAttribute(hConsole, 2);
				total += it2.value + 1;
			}
			else
				SetConsoleTextAttribute(hConsole, 7);
			std::cout << it2.value;
		}
		std::cout << "\n";
	}

	std::cout << "Total risk level: " << total;
}