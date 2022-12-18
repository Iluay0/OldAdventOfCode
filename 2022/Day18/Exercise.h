#pragma once

enum Type
{
	None = 0,
	Solid = 1,
	Air = 2
};

struct Position
{
	int x;
	int y;
	int z;

	Position()
	{
		x = 0;
		y = 0;
		z = 0;
	}

	Position(int x, int y, int z)
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}

	std::string toString()
	{
		return std::to_string(x) + "," + std::to_string(y) + "," + std::to_string(z);
	}

	bool operator==(const Position& other) const {
		return this->x == other.x &&
			this->y == other.y &&
			this->z == other.z;
	}
};

struct Cube
{
	int index;
	Position position;
	Type type;

	Cube(int index, int x, int y, int z)
	{
		this->position = Position(x, y, z);
		this->index = index;
		this->type = Type::None;
	}

	Cube(int index, int x, int y, int z, Type type)
	{
		this->position = Position(x, y, z);
		this->index = index;
		this->type = type;
	}

	bool isTouching(const Cube& other)
	{
		Position newPos = position;
		newPos.x++;
		if (newPos == other.position)
			return true;
		newPos = position;
		newPos.x--;
		if (newPos == other.position)
			return true;

		newPos = position;
		newPos.y++;
		if (newPos == other.position)
			return true;
		newPos = position;
		newPos.y--;
		if (newPos == other.position)
			return true;

		newPos = position;
		newPos.z++;
		if (newPos == other.position)
			return true;
		newPos = position;
		newPos.z--;
		if (newPos == other.position)
			return true;

		return false;
	}
};

class Exercise
{
	int xMax;
	int yMax;
	int zMax;
	std::map<int, Cube> cubes;
	void eraseOutsideCubes();
	void checkAirPockets();
	bool cubeExists(Position position);
public:
	void Part1(std::list<std::string> inputs);
	void Part2(std::list<std::string> inputs);

	static Exercise* inst()
	{
		static Exercise instance;
		return &instance;
	}
};