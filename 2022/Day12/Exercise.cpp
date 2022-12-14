#include "../../Utils/Utils.h"
#include "Exercise.h"

void Exercise::Part1(std::list<std::string> inputs)
{
	HeightMap heightMap;
	heightMap.readInput(inputs);

	if (heightMap.pStartPos == nullptr || heightMap.pDestPos == nullptr)
		throw;

	heightMap.path(heightMap.pStartPos->index, 0);
	std::cout << "Steps: " << heightMap.shortestPath;
}

void Exercise::Part2(std::list<std::string> inputs)
{
	HeightMap heightMap;
	heightMap.readInput(inputs);

	if (heightMap.pStartPos == nullptr || heightMap.pDestPos == nullptr)
		throw;

	heightMap.reversePath(heightMap.pDestPos->index, 0);
	std::cout << "Steps: " << heightMap.shortestPath;
}