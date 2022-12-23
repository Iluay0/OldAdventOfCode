#include "../../Utils/Utils.h"
#include "Exercise.h"

void Exercise::read(std::list<std::string> inputs)
{
	int y = 0;
	for (auto& it : inputs)
	{
		int x = 0;
		for (auto& it2 : it)
		{
			if (it2 == '#')
				elves.insert({ { x, y }, Elf(x, y) });
			x++;
		}
		y++;
	}
}

void Exercise::render()
{
	std::pair<int, int> minMaxX = { INT_MAX, INT_MAX };
	std::pair<int, int> minMaxY = { INT_MAX, INT_MAX };
	for (auto& it : elves)
	{
		if (minMaxX.first == INT_MAX || it.first.first < minMaxX.first)
			minMaxX.first = it.first.first - 1;
		if (minMaxX.second == INT_MAX || it.first.first > minMaxX.second)
			minMaxX.second = it.first.first + 1;
		if (minMaxY.first == INT_MAX || it.first.second < minMaxY.first)
			minMaxY.first = it.first.second - 1;
		if (minMaxY.second == INT_MAX || it.first.second > minMaxY.second)
			minMaxY.second = it.first.second + 1;
	}

	std::string render = "";
	for (int y = minMaxY.first; y <= minMaxY.second; y++)
	{
		for (int x = minMaxX.first; x <= minMaxX.second; x++)
		{
			if (elves.count({ x, y }))
				render += "#";
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
	coord.Y = static_cast<short>(minMaxY.second - minMaxY.first + 1);
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
	std::this_thread::sleep_for(std::chrono::milliseconds(1000));
}

void Exercise::Part1(std::list<std::string> inputs)
{
	directions = { Direction::North, Direction::South, Direction::West, Direction::East };
	read(inputs);

	for (int i = 0; i < 10; i++)
	{
		std::map<std::pair<int, int>, Elf> newElves;
		// Propose a direction
		for (auto& it : elves)
		{
			it.second.proposeDirection(elves, directions);
		}

		// Move
		for (auto& it : elves)
		{
			auto count = std::count_if(elves.begin(), elves.end(),
				[&it](const std::pair<std::pair<int, int>, Elf> pair)
				{
					return pair.second.proposedDirection == it.second.proposedDirection;
				});

			if (count <= 1 && it.second.proposedDirection != std::make_pair(INT_MAX, INT_MAX))
			{
				it.second.x = it.second.proposedDirection.first;
				it.second.y = it.second.proposedDirection.second;
				newElves.insert({ it.second.proposedDirection, it.second });
			}
			else
				newElves.insert({ it.first, it.second });
		}

		// Reset
		elves.clear();
		elves = newElves;
		newElves.clear();
		for (auto& it : elves)
		{
			it.second.proposedDirection = { INT_MAX, INT_MAX };
		}

		auto direction = directions.front();
		directions.erase(directions.begin());
		directions.push_back(direction);

		// render();
	}

	std::pair<int, int> minMaxX = { INT_MAX, INT_MAX };
	std::pair<int, int> minMaxY = { INT_MAX, INT_MAX };
	for (auto& it : elves)
	{
		if (minMaxX.first == INT_MAX || it.first.first < minMaxX.first)
			minMaxX.first = it.first.first;
		if (minMaxX.second == INT_MAX || it.first.first > minMaxX.second)
			minMaxX.second = it.first.first;
		if (minMaxY.first == INT_MAX || it.first.second < minMaxY.first)
			minMaxY.first = it.first.second;
		if (minMaxY.second == INT_MAX || it.first.second > minMaxY.second)
			minMaxY.second = it.first.second;
	}

	std::cout << (((minMaxY.second + 1) - minMaxY.first) * ((minMaxX.second + 1) - minMaxX.first)) - elves.size();

}

void Exercise::Part2(std::list<std::string> inputs)
{
	directions = { Direction::North, Direction::South, Direction::West, Direction::East };
	read(inputs);

	int i = 1;
	while(true)
	{
		std::map<std::pair<int, int>, Elf> newElves;
		// Propose a direction
		for (auto& it : elves)
		{
			it.second.proposeDirection(elves, directions);
		}

		int moved = 0;
		// Move
		for (auto& it : elves)
		{
			auto count = std::count_if(elves.begin(), elves.end(),
				[&it](const std::pair<std::pair<int, int>, Elf> pair)
				{
					return pair.second.proposedDirection == it.second.proposedDirection;
				});

			if (count <= 1 && it.second.proposedDirection != std::make_pair(INT_MAX, INT_MAX))
			{
				it.second.x = it.second.proposedDirection.first;
				it.second.y = it.second.proposedDirection.second;
				newElves.insert({ it.second.proposedDirection, it.second });
				moved++;
			}
			else
				newElves.insert({ it.first, it.second });
		}

		if (moved == 0)
			break;

		// Reset
		elves.clear();
		elves = newElves;
		newElves.clear();
		for (auto& it : elves)
		{
			it.second.proposedDirection = { INT_MAX, INT_MAX };
		}

		auto direction = directions.front();
		directions.erase(directions.begin());
		directions.push_back(direction);

		// render();
		i++;
	}

	std::cout << i;
}