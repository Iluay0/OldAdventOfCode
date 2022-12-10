#include "../../Utils/Utils.h"
#include "Exercise.h"

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
			if(headPos.y > y)
				y = headPos.y - 1;
			else if(headPos.y < y)
				y = headPos.y + 1;
			if(headPos.x > x)
				x = headPos.x - 1;
			else if(headPos.x < x)
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

void Exercise::Part1(std::list<std::string> inputs)
{
	std::vector<Knot> knots = {
		{0, 0},
		{0, 0}
	};

	for (auto& it : inputs)
	{
		auto split = Utils::split(it, " ");
		int moves = stoi(split[1]);

		if (split[0] == "U")
		{
			int dest = knots[0].y - moves;
			for (int i = knots[0].y; i >= dest; i--)
			{
				knots[0].y = i;
				knots[1].moveToHead(knots[0]);
			}
		}
		else if (split[0] == "D")
		{
			int dest = knots[0].y + moves;
			for (int i = knots[0].y; i <= dest; i++)
			{
				knots[0].y = i;
				knots[1].moveToHead(knots[0]);
			}
		}
		else if (split[0] == "L")
		{
			int dest = knots[0].x - moves;
			for (int i = knots[0].x; i >= dest; i--)
			{
				knots[0].x = i;
				knots[1].moveToHead(knots[0]);
			}
		}
		else if (split[0] == "R")
		{
			int dest = knots[0].x + moves;
			for (int i = knots[0].x; i <= dest; i++)
			{
				knots[0].x = i;
				knots[1].moveToHead(knots[0]);
			}
		}
	}

	std::cout << knots[1].visited.size();
}

void Exercise::Part2(std::list<std::string> inputs)
{
	std::vector<Knot> knots;
	for (int i = 0; i < 10; i++)
		knots.push_back({ 0, 0 });

	for (auto& it : inputs)
	{
		auto split = Utils::split(it, " ");
		int moves = stoi(split[1]);

		if (split[0] == "U")
		{
			int dest = knots[0].y - moves;
			for (int i = knots[0].y; i >= dest; i--)
			{
				knots[0].y = i;
				for (auto it2 = std::next(knots.begin()); it2 != knots.end(); it2++)
				{
					it2->moveToHead(*std::prev(it2));
				}
			}
		}
		else if (split[0] == "D")
		{
			int dest = knots[0].y + moves;
			for (int i = knots[0].y; i <= dest; i++)
			{
				knots[0].y = i;
				for (auto it2 = std::next(knots.begin()); it2 != knots.end(); it2++)
				{
					it2->moveToHead(*std::prev(it2));
				}
			}
		}
		else if (split[0] == "L")
		{
			int dest = knots[0].x - moves;
			for (int i = knots[0].x; i >= dest; i--)
			{
				knots[0].x = i;
				for (auto it2 = std::next(knots.begin()); it2 != knots.end(); it2++)
				{
					it2->moveToHead(*std::prev(it2));
				}
			}
		}
		else if (split[0] == "R")
		{
			int dest = knots[0].x + moves;
			for (int i = knots[0].x; i <= dest; i++)
			{
				knots[0].x = i;
				for (auto it2 = std::next(knots.begin()); it2 != knots.end(); it2++)
				{
					it2->moveToHead(*std::prev(it2));
				}
			}
		}
	}

	std::cout << knots[9].visited.size();
}