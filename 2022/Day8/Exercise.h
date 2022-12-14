#pragma once

enum Visibility
{
	None = 0x0,
	Top = 0x1,
	Left = 0x2,
	Right = 0x4,
	Bottom = 0x8
};

class Exercise
{
	std::vector<std::vector<int>> treeHeights;

	int getVisibility(int x, int y);
	int getScore(int x, int y);
public:
	void Part1(std::list<std::string> inputs);
	void Part2(std::list<std::string> inputs);

	static Exercise* inst()
	{
		static Exercise instance;
		return &instance;
	}
};