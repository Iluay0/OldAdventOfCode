#pragma once

struct Knot
{
	int x;
	int y;
	std::set<std::pair<int, int>> visited;

	Knot(int xx, int yy)
	{
		x = xx;
		y = yy;
		visited.insert({ x, y });
	}

	int getPosDiff(const Knot& other)
	{
		return abs(other.x - x) + abs(other.y - y);
	}

	void dragTail(const Knot& headPos)
	{
		if (abs(headPos.x - x) == abs(headPos.y - y))
		{
			if (headPos.y > y)
				y = headPos.y - 1;
			else if (headPos.y < y)
				y = headPos.y + 1;
			if (headPos.x > x)
				x = headPos.x - 1;
			else if (headPos.x < x)
				x = headPos.x + 1;
		}
		else if (abs(headPos.x - x) > abs(headPos.y - y))
			y = headPos.y;
		else
			x = headPos.x;
	}

	void moveToHead(const Knot& headPos)
	{
		if (getPosDiff(headPos) > 2)
			dragTail(headPos);

		if (headPos.x > x + 1)
			x++;
		else if (headPos.x < x - 1)
			x--;
		if (headPos.y > y + 1)
			y++;
		else if (headPos.y < y - 1)
			y--;

		visited.insert({ x, y });
	}

	bool hasVisited(int xx, int yy)
	{
		auto it = std::find_if(visited.begin(), visited.end(),
			[&xx, &yy](const std::pair<int, int>& pos) {
				return pos.first == xx && pos.second == yy;
			});
		if (it != visited.end())
			return true;
		return false;
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