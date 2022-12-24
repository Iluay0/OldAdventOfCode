#include "../../Utils/Utils.h"
#include "Exercise.h"

void Exercise::read(std::list<std::string> inputs)
{
	minMaxX = { INT_MAX, INT_MAX };
	minMaxY = { INT_MAX, INT_MAX };

	int y = 0;
	for (auto& it : inputs)
	{
		int x = 0;
		for (auto& it2 : it)
		{
			switch (it2)
			{
				case '#':
					tiles[{ x, y }].push_back(Tile(x, y, TileType::Rock));
					break;
				case '>':
				case 'v':
				case '<':
				case '^':
					tiles[{ x, y }].push_back(Tile(x, y, it2));
					break;
			}
			x++;
		}
		y++;
	}

	for (auto& it : tiles)
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
	startLocation = { 1, 0 };
	destLocation = { minMaxX.second - 1, minMaxY.second };
}

void Exercise::render()
{
	std::string render = "";
	for (int y = minMaxY.first; y <= minMaxY.second; y++)
	{
		for (int x = minMaxX.first; x <= minMaxX.second; x++)
		{
			int elfCount = 0;
			for (auto& it : elves)
			{
				if (!it.isDead && it.currentLocation == std::make_pair(x, y))
				{
					elfCount++;
				}
			}
			if (elfCount > 0)
			{
				render += "\x1b[33m";
				if (elfCount < 10)
					render += std::to_string(elfCount);
				else
					render += "+";
				render += "\x1b[0m";
				continue;
			}

			if (destLocation == std::make_pair(x, y))
			{
				render += "S";
				continue;
			}

			if (tiles[{ x, y }].empty())
			{
				render += " ";
				continue;
			}

			switch (tiles[{x, y}].front().tileType)
			{
				case TileType::Rock:
					render += "#";
					break;
				case TileType::Blizzard:
					render += tiles[{x, y}].front().direction;
					break;
				default:
					render += '.';
			}
		}
		render += "\n";
	}

	COORD coord;
	coord.X = 0;
	coord.Y = 0;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
	std::this_thread::sleep_for(std::chrono::milliseconds(100));

	std::cout << render;
}

void Exercise::generateElves()
{
	for (int i = 0; i < 8; i++)
	{
		elves.push_back(Elf(startLocation, i));
	}
}

void Exercise::blizzardBehaviour(bool simulate)
{
	auto it = tiles.begin();
	auto itEnd = tiles.end();

	std::map<std::pair<int, int>, std::list<Tile>> fakeTiles(tiles);
	if (simulate)
	{
		it = fakeTiles.begin();
		itEnd = fakeTiles.end();
	}

	for (it; it != itEnd; it++)
	{
		for (auto it2 = it->second.begin(); it2 != it->second.end(); /* it++ */)
		{
			if (it2->tileType != TileType::Blizzard || it2->moved)
			{
				it2++;
				continue;
			}

			std::pair<int, int> newLocation = it->first;
			switch (it2->direction)
			{
			case '>':
				newLocation.first++;
				break;
			case 'v':
				newLocation.second++;
				break;
			case '<':
				newLocation.first--;
				break;
			case '^':
				newLocation.second--;
				break;
			}

			bool empty = tiles[newLocation].empty();
			if (simulate)
				empty = fakeTiles[newLocation].empty();

			if (!empty)
			{
				auto tileType = TileType::Rock;
				if (!simulate && !tiles[newLocation].empty())
					tileType = tiles[newLocation].front().tileType;
				else if (simulate && !fakeTiles[newLocation].empty())
					tileType = fakeTiles[newLocation].front().tileType;
				else throw;

				if (tileType == TileType::Rock)
				{
					switch (it2->direction)
					{
					case '>':
						newLocation.first = minMaxX.first + 1;
						break;
					case 'v':
						newLocation.second = minMaxY.first + 1;
						break;
					case '<':
						newLocation.first = minMaxX.second - 1;
						break;
					case '^':
						newLocation.second = minMaxY.second - 1;
						break;
					}
				}
			}

			it2->moved = true;

			if(simulate)
				fakeTiles[newLocation].push_back(*it2);
			else
				tiles[newLocation].push_back(*it2);

			it2 = it->second.erase(it2);

			if (!simulate)
			{
				std::for_each(elves.begin(), elves.end(),
					[&newLocation](Elf& elf) {
						if (elf.currentLocation == newLocation)
							elf.isDead = true;
					});
			}
		}
	}

	if (!simulate)
	{
		for (auto& it : tiles)
		{
			for (auto& it2 : it.second)
			{
				it2.moved = false;
			}
		}
	}
	else
	{
		for (auto it = elves.begin(); it != elves.end(); /* it++ */)
		{
			if (it->isDead)
			{
				it = elves.erase(it);
				elvesKilled++;
			}
			else
			{
				it->tryMove(fakeTiles);
				it++;
			}
		}
	}
}

void Exercise::Part1(std::list<std::string> inputs)
{
	read(inputs);

	elvesKilled = 0;
	steps = 0;

	auto dest = destLocation;
	auto it = std::find_if(elves.begin(), elves.end(),
		[&dest](const Elf& elf) {
			return !elf.isDead && elf.currentLocation == dest;
		});

	while (it == elves.end())
	{
		generateElves();
		blizzardBehaviour(true);
		blizzardBehaviour();
		render();
		steps++;

		it = std::find_if(elves.begin(), elves.end(),
			[&dest](const Elf& elf) {
				return !elf.isDead && elf.currentLocation == dest;
			});

		COORD coord;
		coord.X = 0;
		coord.Y = static_cast<short>(minMaxY.second - minMaxY.first + 1);
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
		std::cout << "Current Total Steps: " << steps << std::endl;
		std::cout << "Elves generated: " << elves.size() << std::endl;
		std::cout << "Elves killed: " << elvesKilled << std::endl;
	}
}

void Exercise::Part2(std::list<std::string> inputs)
{

}