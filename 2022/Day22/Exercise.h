#pragma once

enum Direction: int
{
	Right = 0,
	Bottom,
	Left,
	Top
};

enum Tile
{
	Empty = 0,
	Walkable,
	Wall
};

class Exercise
{
	std::vector<std::vector<Tile>> board;
	std::string password;

	std::pair<int, int> currentPosition;
	Direction currentDirection = Direction::Right;

	void move(int amount);
	void read(std::list<std::string> inputs);
	void changeDirection(char direction);
	void render();
public:
	void Part1(std::list<std::string> inputs);
	void Part2(std::list<std::string> inputs);

	static Exercise* inst()
	{
		static Exercise instance;
		return &instance;
	}
};