#include "../../Utils/Utils.h"
#include "Exercise.h"

#define TERRAIN_WIDTH 7

void Exercise::render(const std::deque<std::deque<int>>& currentShape, const std::pair<int, int>& shapePos)
{
	std::string render = "";
	for (int y = 0; y < terrain.size(); y++)
	{
		for (int x = 0; x < terrain[y].size(); x++)
		{
			if (terrain[y][x])
				render += "#";
			else if (y - shapePos.second < currentShape.size() && x - shapePos.first < currentShape[y - shapePos.second].size() &&
				currentShape[y - shapePos.second][x - shapePos.first] == 1)
				render += "@";
			else
				render += ".";
		}
		render += "\n";
	}

	COORD coord;
	coord.X = 0;
	coord.Y = 0;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);

	std::cout << render;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
	std::this_thread::sleep_for(std::chrono::milliseconds(100));
}

void Exercise::setup()
{
	for (int y = 0; y < 4; y++)
	{
		std::deque<bool> line;
		for (int x = 0; x < TERRAIN_WIDTH; x++)
		{
			line.push_back(false);
		}
		terrain.push_back(line);
	}

	shapes.push_back({
		{ 1, 1, 1, 1 }
		});

	shapes.push_back({
		{ 0, 1, 0 },
		{ 1, 1, 1 },
		{ 0, 1, 0 }
		});

	shapes.push_back({
		{ 0, 0, 1 },
		{ 0, 0, 1 },
		{ 1, 1, 1 }
		});

	shapes.push_back({
		{ 1 },
		{ 1 },
		{ 1 },
		{ 1 }
		});

	shapes.push_back({
		{ 1, 1 },
		{ 1, 1 }
		});

	currentShapeIndex = 0;
}

void Exercise::tetris(__int64& highestPoint, std::pair<__int64, __int64>& shapePos, std::string& pattern, __int64& patternIndex, __int64 iterations)
{
	for (int i = 0; i < iterations; i++)
	{
		auto& currentShape = shapes[currentShapeIndex % shapes.size()];
		currentShapeIndex++;
		while (terrain.size() != highestPoint + 3 + currentShape.size())
		{
			if (terrain.size() < highestPoint + 3 + currentShape.size())
			{
				std::deque<bool> line;
				for (int x = 0; x < TERRAIN_WIDTH; x++)
				{
					line.push_back(false);
				}
				terrain.insert(terrain.begin(), line);
			}
			else
				terrain.erase(terrain.begin());
		}
		shapePos = { 2, 0 };
		while (true)
		{
			char jet = pattern[patternIndex % pattern.size()];
			patternIndex++;
			if (jet == '<')
			{
				shapePos.first--;
				if (shapePos.first < 0)
					shapePos.first = 0;
			}
			else
			{
				shapePos.first++;
				if (shapePos.first > TERRAIN_WIDTH - 1)
					shapePos.first = TERRAIN_WIDTH - 1;
			}

			// out of bounds check
			for (size_t y = 0; y < currentShape.size(); y++)
			{
				for (size_t x = 0; x < currentShape[y].size(); x++)
				{
					if (shapePos.first + x > TERRAIN_WIDTH - 1)
						shapePos.first = (TERRAIN_WIDTH - 1) - x;
				}
			}

			// collision check (jet)
			bool collision = false;
			for (size_t y = 0; y < currentShape.size(); y++)
			{
				for (size_t x = 0; x < currentShape[y].size(); x++)
				{
					if (currentShape[y][x] == 1 && terrain[shapePos.second + y][shapePos.first + x] == true)
					{
						collision = true;
						break;
					}
				}
				if (collision)
					break;
			}
			if (collision)
			{
				if (jet == '<')
					shapePos.first++;
				else
					shapePos.first--;
			}

			// render(currentShape, shapePos);

			bool placeShape = false;
			// collision check (down)
			for (size_t y = 0; y < currentShape.size(); y++)
			{
				for (size_t x = 0; x < currentShape[y].size(); x++)
				{
					if (shapePos.second + y + 1 >= terrain.size())
					{
						placeShape = true;
						break;
					}
					if (currentShape[y][x] == 1 && terrain[shapePos.second + y + 1][shapePos.first + x] == true)
					{
						placeShape = true;
						break;
					}
				}
				if (placeShape)
					break;
			}
			if (placeShape)
			{
				if (terrain.size() - shapePos.second > highestPoint)
					highestPoint = terrain.size() - shapePos.second;
				for (size_t y = 0; y < currentShape.size(); y++)
				{
					for (size_t x = 0; x < currentShape[y].size(); x++)
					{
						if (currentShape[y][x] == 1)
						{
							terrain[shapePos.second + y][shapePos.first + x] = true;
						}
					}
				}
				break;
			}

			// move shape down
			shapePos.second++;
		}
	}
}

void Exercise::Part1(std::list<std::string> inputs)
{
	setup();

	std::string pattern = inputs.front();
	std::pair<__int64, __int64> shapePos = { 0, 0 };
	__int64 patternIndex = 0;
	__int64 highestPoint = 0;

	tetris(highestPoint, shapePos, pattern, patternIndex, 2022);

	COORD coord;
	coord.X = 0;
	coord.Y = terrain.size() + 1;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
	std::cout << "Tower size: " << highestPoint;
}

void Exercise::Part2(std::list<std::string> inputs)
{
	setup();

	std::string pattern = inputs.front();
	std::pair<__int64, __int64> shapePos = { 0, 0 };
	__int64 patternIndex = 0;
	__int64 highestPoint = 0;

	__int64 oldHighestPoint = 0;
	std::string highestPoints = "";
	std::string highestPoints2 = "";
	for (__int64 i = 0; i < 1000000000000ll; i++)
	{
		tetris(highestPoint, shapePos, pattern, patternIndex, 1);

		highestPoints2 += std::to_string(highestPoint - oldHighestPoint);
		oldHighestPoint = highestPoint;

		if (highestPoints.find(highestPoints2) != std::string::npos)
		{
			std::string test = highestPoints2 + highestPoints2;
			if (highestPoints.find(test) != std::string::npos)
			{
				if (test.size() >= pattern.size() * shapes.size())
				{
					highestPoints += highestPoints2;
					break;
				}
			}
			continue;
		}
		if (highestPoints == highestPoints2)
			break;

		highestPoints += highestPoints2;
		highestPoints2 = "";
	}

	__int64 index = highestPoints.find(highestPoints2);
	__int64 newHighestPoint = 0;
	for (auto& it : highestPoints2)
		newHighestPoint += it - '0';

	int occurrences = 0;
	std::string::size_type pos = 0;
	while ((pos = highestPoints.find(highestPoints2, pos)) != std::string::npos) {
		++occurrences;
		pos += highestPoints2.length();
	}
	newHighestPoint *= occurrences;

	highestPoints = highestPoints.substr(0, index);
	__int64 multiplier = 1000000000000ll / (highestPoints2.size() * occurrences);
	newHighestPoint *= multiplier;
	for (size_t j = 0; j < index; j++)
	{
		newHighestPoint += highestPoints[j] - '0';
	}

	__int64 remainder = 1000000000000ll % (highestPoints2.size() * occurrences) - highestPoints.size();
	tetris(highestPoint, shapePos, pattern, patternIndex, remainder);
	newHighestPoint += highestPoint - oldHighestPoint;

	COORD coord;
	coord.X = 0;
	coord.Y = terrain.size() + 1;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
	std::cout << "Tower size: " << newHighestPoint;
}