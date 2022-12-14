#include "../../Utils/Utils.h"
#include "Exercise.h"

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