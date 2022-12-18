#pragma once

class Exercise
{
	std::deque<std::deque<std::deque<int>>> shapes;
	std::deque<std::deque<bool>> terrain;
	__int64 currentShapeIndex;
public:
	void setup();
	void render(const std::deque<std::deque<int>>& currentShape, const std::pair<int, int>& shapePos);
	void Part1(std::list<std::string> inputs);
	void Part2(std::list<std::string> inputs);
	void tetris(__int64& highestPoint, std::pair<__int64, __int64>& shapePos, std::string& pattern, __int64& patternIndex, __int64 iterations);

	static Exercise* inst()
	{
		static Exercise instance;
		return &instance;
	}
};