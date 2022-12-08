#include "../../Utils/Utils.h"
#include "Exercise.h"

enum Visibility
{
	None = 0x0,
	Top = 0x1,
	Left = 0x2,
	Right = 0x4,
	Bottom = 0x8
};

int getVisibility(std::vector<std::vector<int>>& treeHeights, int x, int y)
{
	int visibility = 0x0;

	if (x == 0)
		visibility |= Visibility::Left;
	if (y == 0)
		visibility |= Visibility::Top;
	if (x == treeHeights.size() - 1)
		visibility |= Visibility::Right;
	if (y == treeHeights[x].size() - 1)
		visibility |= Visibility::Bottom;

	if (visibility != 0x0)
		return visibility;

	visibility = Visibility::Left | Visibility::Right | Visibility::Top | Visibility::Bottom;

	int curValue = treeHeights[x][y];
	for (int i = x - 1; i >= 0; i--)
	{
		if (treeHeights[i][y] >= curValue && (visibility & Visibility::Left))
			visibility &= ~Visibility::Left;
	}
	for (int i = x + 1; i < treeHeights.size(); i++)
	{
		if (treeHeights[i][y] >= curValue && (visibility & Visibility::Right))
			visibility &= ~Visibility::Right;
	}
	for (int i = y - 1; i >= 0; i--)
	{
		if (treeHeights[x][i] >= curValue && (visibility & Visibility::Top))
			visibility &= ~Visibility::Top;
	}
	for (int i = y + 1; i < treeHeights[x].size(); i++)
	{
		if (treeHeights[x][i] >= curValue && (visibility & Visibility::Bottom))
			visibility &= ~Visibility::Bottom;
	}

	return visibility;
}

int getScore(std::vector<std::vector<int>>& treeHeights, int x, int y)
{
	int score = 1;

	int curValue = treeHeights[x][y];
	for (int i = x - 1; i >= 0; i--)
	{
		if (treeHeights[i][y] >= curValue)
		{
			score *= x - i;
			break;
		}
		if (i == 0)
			score *= x - i;
	}
	for (int i = x + 1; i < treeHeights.size(); i++)
	{
		if (treeHeights[i][y] >= curValue)
		{
			score *= i - x;
			break;
		}
		if (i == treeHeights.size() - 1)
			score *= i - x;
	}
	for (int i = y - 1; i >= 0; i--)
	{
		if (treeHeights[x][i] >= curValue)
		{
			score *= y - i;
			break;
		}
		if (i == 0)
			score *= y - i;
	}
	for (int i = y + 1; i < treeHeights[x].size(); i++)
	{
		if (treeHeights[x][i] >= curValue)
		{
			score *= i - y;
			break;
		}
		if (i == treeHeights[x].size() - 1)
			score *= i - y;
	}

	return score;
}

void Exercise::Part1(std::list<std::string> inputs)
{
	std::vector<std::vector<int>> treeHeights;
	for (auto& it : inputs)
	{
		std::vector<int> line;
		for (auto& it2 : it)
		{
			line.push_back(it2 - '0');
		}
		treeHeights.push_back(line);
	}

	int visible = 0;
	for (int x = 0; x < treeHeights.size(); x++)
	{
		for (int y = 0; y < treeHeights[x].size(); y++)
		{
			if (getVisibility(treeHeights, x, y) != Visibility::None)
				visible++;
		}
	}
	std::cout << visible;
}

void Exercise::Part2(std::list<std::string> inputs)
{
	std::vector<std::vector<int>> treeHeights;
	for (auto& it : inputs)
	{
		std::vector<int> line;
		for (auto& it2 : it)
		{
			line.push_back(it2 - '0');
		}
		treeHeights.push_back(line);
	}

	int score = 0;
	for (int x = 0; x < treeHeights.size(); x++)
	{
		for (int y = 0; y < treeHeights[x].size(); y++)
		{
			int newScore = getScore(treeHeights, x, y);
			if (newScore > score)
				score = newScore;
		}
	}
	std::cout << score;
}