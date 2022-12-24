#pragma once

enum Direction
{
	Right = 0,
	Bottom,
	Left,
	Top
};

enum TileType
{
	None = 0,
	Rock,
	Blizzard
};

struct Tile
{
	int x;
	int y;
	TileType tileType;
	char direction;
	bool moved;

	Tile()
	{
		this->x = 0;
		this->y = 0;
		this->tileType = TileType::None;
		this->direction = '>';
		this->moved = false;
	}

	Tile(int x, int y, TileType tileType)
	{
		this->x = x;
		this->y = y;
		this->tileType = tileType;
		this->direction = '>';
		this->moved = false;
	}

	Tile(int x, int y, char direction)
	{
		this->x = x;
		this->y = y;
		this->tileType = TileType::Blizzard;
		this->direction = direction;
		this->moved = false;
	}
};

struct Elf
{
	std::pair<int, int> currentLocation;
	bool isDead;
	int aiType;

	Elf(std::pair<int, int> currentLocation, int aiType)
	{
		this->currentLocation = currentLocation;
		this->isDead = false;
		this->aiType = aiType;
	}

	void tryMove(std::map<std::pair<int, int>, std::list<Tile>>& fakeTiles)
	{
		switch (aiType)
		{
			case 0:
			{
				// Right, down, up, left
				if (fakeTiles[{ currentLocation.first + 1, currentLocation.second }].empty())
					currentLocation.first++;
				else if (fakeTiles[{ currentLocation.first, currentLocation.second + 1 }].empty())
					currentLocation.second++;
				else if (fakeTiles[{ currentLocation.first, currentLocation.second - 1 }].empty())
					currentLocation.second--;
				else if (fakeTiles[{ currentLocation.first - 1, currentLocation.second }].empty())
					currentLocation.first--;
			} break;
			case 1:
			{
				// Down, right, left, up
				if (fakeTiles[{ currentLocation.first, currentLocation.second + 1 }].empty())
					currentLocation.second++;
				else if (fakeTiles[{ currentLocation.first + 1, currentLocation.second }].empty())
					currentLocation.first++;
				if (fakeTiles[{ currentLocation.first - 1, currentLocation.second }].empty())
					currentLocation.first--;
				else if (fakeTiles[{ currentLocation.first, currentLocation.second - 1 }].empty())
					currentLocation.second--;
			} break;
			case 2:
			{
				// Right, down, left, up
				if (fakeTiles[{ currentLocation.first + 1, currentLocation.second }].empty())
					currentLocation.first++;
				else if (fakeTiles[{ currentLocation.first, currentLocation.second + 1 }].empty())
					currentLocation.second++;
				if (fakeTiles[{ currentLocation.first - 1, currentLocation.second }].empty())
					currentLocation.first--;
				else if (fakeTiles[{ currentLocation.first, currentLocation.second - 1 }].empty())
					currentLocation.second--;
			} break;
			case 3:
			{
				// Down, right, up, left
				if (fakeTiles[{ currentLocation.first, currentLocation.second + 1 }].empty())
					currentLocation.second++;
				else if (fakeTiles[{ currentLocation.first + 1, currentLocation.second }].empty())
					currentLocation.first++;
				if (fakeTiles[{ currentLocation.first, currentLocation.second - 1 }].empty())
					currentLocation.second--;
				else if (fakeTiles[{ currentLocation.first - 1, currentLocation.second }].empty())
					currentLocation.first--;
			} break;
			case 4:
			{
				// Right, down, wait, up, left
				if (fakeTiles[{ currentLocation.first + 1, currentLocation.second }].empty())
					currentLocation.first++;
				else if (fakeTiles[{ currentLocation.first, currentLocation.second + 1 }].empty())
					currentLocation.second++;
				else if (!fakeTiles[currentLocation].empty())
				{
					if (fakeTiles[{ currentLocation.first, currentLocation.second - 1 }].empty())
						currentLocation.second--;
					else if (fakeTiles[{ currentLocation.first - 1, currentLocation.second }].empty())
						currentLocation.first--;
				}
			} break;
			case 5:
			{
				// Down, right, wait, up, left
				if (fakeTiles[{ currentLocation.first, currentLocation.second + 1 }].empty())
					currentLocation.second++;
				else if (fakeTiles[{ currentLocation.first + 1, currentLocation.second }].empty())
					currentLocation.first++;
				else if (!fakeTiles[currentLocation].empty())
				{
					if (fakeTiles[{ currentLocation.first, currentLocation.second - 1 }].empty())
						currentLocation.second--;
					else if (fakeTiles[{ currentLocation.first - 1, currentLocation.second }].empty())
						currentLocation.first--;
				}
			} break;
			case 6:
			{
				// Right, down, wait, left, up
				if (fakeTiles[{ currentLocation.first + 1, currentLocation.second }].empty())
					currentLocation.first++;
				else if (fakeTiles[{ currentLocation.first, currentLocation.second + 1 }].empty())
					currentLocation.second++;
				else if (!fakeTiles[currentLocation].empty())
				{
					if (fakeTiles[{ currentLocation.first - 1, currentLocation.second }].empty())
						currentLocation.first--;
					else if (fakeTiles[{ currentLocation.first, currentLocation.second - 1 }].empty())
						currentLocation.second--;
				}
			} break;
			case 7:
			{
				// Down, right, wait, left, up
				if (fakeTiles[{ currentLocation.first, currentLocation.second + 1 }].empty())
					currentLocation.second++;
				else if (fakeTiles[{ currentLocation.first + 1, currentLocation.second }].empty())
					currentLocation.first++;
				else if (!fakeTiles[currentLocation].empty())
				{
					if (fakeTiles[{ currentLocation.first - 1, currentLocation.second }].empty())
						currentLocation.first--;
					else if (fakeTiles[{ currentLocation.first, currentLocation.second - 1 }].empty())
						currentLocation.second--;
				}
			} break;
		}
	}
};

class Exercise
{
	std::pair<int, int> minMaxX;
	std::pair<int, int> minMaxY;

	std::pair<int, int> startLocation;
	std::pair<int, int> destLocation;
	
	int elvesKilled;
	int steps;
	std::deque<Elf> elves;
	std::map<std::pair<int, int>, std::list<Tile>> tiles;

	void generateElves();
	void blizzardBehaviour(bool simulate = false);
	void read(std::list<std::string> inputs);

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