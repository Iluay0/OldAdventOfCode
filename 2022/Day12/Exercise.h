#pragma once

const std::vector<std::pair<int, int>> directions = {
	{0, -1}, // up
	{0, +1}, // down
	{-1, 0}, // left
	{+1, 0}  // right
};

struct Point
{
	int index;
	uint32_t shortestDist;
	char elevation;
	bool visited;

	Point(int id, char el)
	{
		index = id;
		elevation = el;
		visited = false;
		shortestDist = -1;
	}
};

struct HeightMap
{
	std::map<int, Point*> points;

	Point* pStartPos;
	Point* pDestPos;
	int width;
	int height;
	uint32_t shortestPath;

	HeightMap()
	{
		width = 0;
		height = 0;
		pStartPos = nullptr;
		pDestPos = nullptr;
		shortestPath = -1;
	}

	std::pair<int, int> getCoords(Point* pPoint)
	{
		return { pPoint->index % width, pPoint->index / width };
	}

	void path(int index, int currentSteps)
	{
		auto& pPoint = points[index];
		auto [x, y] = getCoords(pPoint);

		if (pPoint->visited && currentSteps >= pPoint->shortestDist)
			return;

		if (pPoint->shortestDist < currentSteps || currentSteps >= shortestPath)
			return;

		pPoint->shortestDist = currentSteps;

		for (auto& [dx, dy] : directions)
		{
			int destX = x + dx;
			int destY = y + dy;

			if (destX < 0 || destX == width || destY < 0 || destY == height)
				continue;

			int destIndex = destY * width + destX;
			Point* pDestPoint = points[destIndex];
			if (pDestPoint->elevation > pPoint->elevation + 1)
				continue;

			if (pDestPoint->index == pDestPos->index)
			{
				shortestPath = currentSteps + 1;
				return;
			}

			/*
			if (!pPoint->visited)
				render(pPoint->index, pDestPoint->index);
				*/
			pPoint->visited = true;

			path(destIndex, currentSteps + 1);
		}
	}

	void reversePath(int index, int currentSteps)
	{
		auto& pPoint = points[index];
		auto [x, y] = getCoords(pPoint);

		if (pPoint->visited && currentSteps >= pPoint->shortestDist)
			return;

		if (pPoint->shortestDist < currentSteps || currentSteps >= shortestPath)
			return;

		pPoint->shortestDist = currentSteps;

		for (auto& [dx, dy] : directions)
		{
			int destX = x + dx;
			int destY = y + dy;

			if (destX < 0 || destX == width || destY < 0 || destY == height)
				continue;

			int destIndex = destY * width + destX;
			Point* pDestPoint = points[destIndex];
			if (pDestPoint->elevation < pPoint->elevation - 1)
				continue;

			if (pDestPoint->elevation == 'a')
			{
				shortestPath = currentSteps + 1;
				return;
			}

			/*
			if(!pPoint->visited)
				render(pPoint->index, pDestPoint->index);
				*/
			pPoint->visited = true;

			reversePath(destIndex, currentSteps + 1);
		}
	}

	void readInput(std::list<std::string> inputs)
	{
		int index = 0;
		height = inputs.size();
		for (auto& it : inputs)
		{
			width = it.size();
			for (auto& it2 : it)
			{
				Point* point = new Point(index, it2);
				if (it2 == 'S')
				{
					point->elevation = 'a';
					pStartPos = point;
				}
				else if (it2 == 'E')
				{
					point->elevation = 'z';
					pDestPos = point;
				}
				points.insert({ index, point });
				index++;
			}
		}
	}

	void render(int pointIndex, int destPointIndex)
	{
		std::string render = "";
		for (auto& it : points)
		{
			if (it.second->index % width == 0)
				render += "\n";
			if (it.second->index == pointIndex)
				render += "\x1b[36m" + std::string(1, it.second->elevation) + "\x1b[0m";
			else if (it.second->index == destPointIndex)
				render += "\x1b[32m" + std::string(1, it.second->elevation) + "\x1b[0m";
			else if (it.second->visited)
				render += "\x1b[31m" + std::string(1, it.second->elevation) + "\x1b[0m";
			else
				render += it.second->elevation;
		}
		COORD coord;
		coord.X = 0;
		coord.Y = 0;
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
		std::cout << render;
	}
};

class Exercise
{
public:
	void Part1(std::list<std::string> inputs);
	void Part2(std::list<std::string> inputs);

	static Exercise* inst()
	{
		static Exercise instance;
		return &instance;
	}
};