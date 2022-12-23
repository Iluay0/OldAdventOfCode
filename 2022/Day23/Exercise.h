#pragma once

enum Direction
{
	North = 0,
	South,
	West,
	East
};

struct Elf
{
	int x;
	int y;
	std::pair<int, int> proposedDirection;

	Elf()
	{
		this->x = 0;
		this->y = 0;
		this->proposedDirection = { INT_MAX, INT_MAX };
	}

	Elf(int x, int y)
	{
		this->x = x;
		this->y = y;
		this->proposedDirection = { INT_MAX, INT_MAX };
	}

	bool tryProposeDirection(std::map<std::pair<int, int>, Elf>& elves, Direction& direction)
	{
		switch (direction)
		{
		case Direction::North:
			if (!elves.count({ x, y - 1 }) && !elves.count({ x - 1, y - 1 }) && !elves.count({ x + 1, y - 1 }))
			{
				proposedDirection = { x, y - 1 };
				return true;
			}
			break;
		case Direction::South:
			if (!elves.count({ x, y + 1 }) && !elves.count({ x - 1, y + 1 }) && !elves.count({ x + 1, y + 1 }))
			{
				proposedDirection = { x, y + 1 };
				return true;
			}
			break;
		case Direction::West:
			if (!elves.count({ x - 1, y }) && !elves.count({ x - 1, y - 1 }) && !elves.count({ x - 1, y + 1 }))
			{
				proposedDirection = { x - 1, y };
				return true;
			}
			break;
		case Direction::East:
			if (!elves.count({ x + 1, y }) && !elves.count({ x + 1, y - 1 }) && !elves.count({ x + 1, y + 1 }))
			{
				proposedDirection = { x + 1, y };
				return true;
			}
			break;
		}
		return false;
	}

	void proposeDirection(std::map<std::pair<int, int>, Elf>& elves, std::vector<Direction>& directions)
	{
		if (!elves.count({ x - 1, y }) && !elves.count({ x - 1, y - 1 }) && !elves.count({ x - 1, y + 1 }) &&
			!elves.count({ x, y - 1 }) && !elves.count({ x, y + 1 }) &&
			!elves.count({ x + 1, y }) && !elves.count({ x + 1, y - 1 }) && !elves.count({ x + 1, y + 1 }))
			return;

		for (auto& it : directions)
		{
			if (tryProposeDirection(elves, it))
				return;
		}
	}
};

class Exercise
{
	std::vector<Direction> directions;
	std::map<std::pair<int, int>, Elf> elves;
	void render();
	void read(std::list<std::string> inputs);
public:
	void Part1(std::list<std::string> inputs);
	void Part2(std::list<std::string> inputs);

	static Exercise* inst()
	{
		static Exercise instance;
		return &instance;
	}
};