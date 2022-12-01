#include "../../Utils/Utils.h"
#include "Part2.h"

struct HeightPoint
{
	int value;
	bool isLowPoint;
	bool isCounted;

	HeightPoint()
	{
		value = -1;
		isLowPoint = false;
		isCounted = false;
	}
};

extern bool HasNearbyLowPoint(std::vector<std::vector<HeightPoint>>& heightMap, int x, int y);



int GetBasinSize(std::vector<std::vector<HeightPoint>>& heightMap, int x, int y)
{
	int curValue = heightMap[x][y].value;
	int basinSize = 1;
	if (heightMap[x][y].isCounted)
		basinSize = 0;
	heightMap[x][y].isCounted = true;

	if (x > 0 && heightMap[x - 1][y].value < 9 && !heightMap[x - 1][y].isCounted && heightMap[x - 1][y].value >= curValue)
		basinSize += GetBasinSize(heightMap, x - 1, y);
	if (x + 1 < heightMap.size() && heightMap[x + 1][y].value < 9 && !heightMap[x + 1][y].isCounted && heightMap[x + 1][y].value >= curValue)
		basinSize += GetBasinSize(heightMap, x + 1, y);
	if (y > 0 && heightMap[x][y - 1].value < 9 && !heightMap[x][y - 1].isCounted && heightMap[x][y - 1].value >= curValue)
		basinSize += GetBasinSize(heightMap, x, y - 1);
	if (y + 1 < heightMap[x].size() && heightMap[x][y + 1].value < 9 && !heightMap[x][y + 1].isCounted && heightMap[x][y + 1].value >= curValue)
		basinSize += GetBasinSize(heightMap, x, y + 1);

	return basinSize;
}

void Part2::Run(std::list<std::string> inputs)
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
			point.isCounted = false;
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

	std::vector<int> basinSizes;
	for (int x = 0; x < heightMap.size(); x++)
	{
		for (int y = 0; y < heightMap[x].size(); y++)
		{
			if (heightMap[x][y].isLowPoint)
				basinSizes.push_back(GetBasinSize(heightMap, x, y));
		}
	}

	std::sort(basinSizes.begin(), basinSizes.end());
	int total = 1;
	for (int i = basinSizes.size() - 1; i >= basinSizes.size() - 3; i--)
	{
		total *= basinSizes[i];
		std::cout << "Size: " << basinSizes[i] << "\n";
	}

	std::cout << "Multiplied top 3 size: " << total;
}