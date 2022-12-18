#include "../../Utils/Utils.h"
#include "Exercise.h"

void Exercise::eraseOutsideCubes()
{
	// xMax -> 0
	for (int y = yMax; y >= 0; y--)
	{
		for (int z = zMax; z >= 0; z--)
		{
			for (int x = xMax; x >= 0; x--)
			{
				Position position(x, y, z);
				auto it = std::find_if(cubes.begin(), cubes.end(),
					[&position](const std::pair<int, Cube>& pair) {
						return position == pair.second.position;
					});

				if (it != cubes.end())
				{
					if (it->second.type == Type::Solid)
						break;
					cubes.erase(it);
				}
			}
		}
	}


	// yMax -> 0
	for (int x = xMax; x >= 0; x--)
	{
		for (int z = zMax; z >= 0; z--)
		{
			for (int y = yMax; y >= 0; y--)
			{
				Position position(x, y, z);
				auto it = std::find_if(cubes.begin(), cubes.end(),
					[&position](const std::pair<int, Cube>& pair) {
						return position == pair.second.position;
					});

				if (it != cubes.end())
				{
					if (it->second.type == Type::Solid)
						break;
					cubes.erase(it);
				}
			}
		}
	}

	// zMax -> 0
	for (int x = xMax; x >= 0; x--)
	{
		for (int y = yMax; y >= 0; y--)
		{
			for (int z = zMax; z >= 0; z--)
			{
				Position position(x, y, z);
				auto it = std::find_if(cubes.begin(), cubes.end(),
					[&position](const std::pair<int, Cube>& pair) {
						return position == pair.second.position;
					});

				if (it != cubes.end())
				{
					if (it->second.type == Type::Solid)
						break;
					cubes.erase(it);
				}
			}
		}
	}

	// 0 -> xMax
	for (int y = 0; y <= yMax; y++)
	{
		for (int z = 0; z <= zMax; z++)
		{
			for (int x = 0; x <= xMax; x++)
			{
				Position position(x, y, z);
				auto it = std::find_if(cubes.begin(), cubes.end(),
					[&position](const std::pair<int, Cube>& pair) {
						return position == pair.second.position;
					});

				if (it != cubes.end())
				{
					if (it->second.type == Type::Solid)
						break;
					cubes.erase(it);
				}
			}
		}
	}

	// 0 -> yMax
	for (int x = 0; x <= xMax; x++)
	{
		for (int z = 0; z <= zMax; z++)
		{
			for (int y = 0; y <= yMax; y++)
			{
				Position position(x, y, z);
				auto it = std::find_if(cubes.begin(), cubes.end(),
					[&position](const std::pair<int, Cube>& pair) {
						return position == pair.second.position;
					});

				if (it != cubes.end())
				{
					if (it->second.type == Type::Solid)
						break;
					cubes.erase(it);
				}
			}
		}
	}

	// 0 -> zMax
	for (int x = 0; x <= xMax; x++)
	{
		for (int y = 0; y <= yMax; y++)
		{
			for (int z = 0; z <= zMax; z++)
			{
				Position position(x, y, z);
				auto it = std::find_if(cubes.begin(), cubes.end(),
					[&position](const std::pair<int, Cube>& pair) {
						return position == pair.second.position;
					});

				if (it != cubes.end())
				{
					if (it->second.type == Type::Solid)
						break;
					cubes.erase(it);
				}
			}
		}
	}
}

bool Exercise::cubeExists(Position position)
{
	auto it = std::find_if(cubes.begin(), cubes.end(),
		[&position](const std::pair<int, Cube>& pair) {
			return position == pair.second.position;
		});

	return it != cubes.end();
}

void Exercise::checkAirPockets()
{
	for (int x = 0; x <= xMax; x++)
	{
		for (int y = 0; y <= yMax; y++)
		{
			for (int z = 0; z <= zMax; z++)
			{
				Position position(x, y, z);
				auto it = std::find_if(cubes.begin(), cubes.end(),
					[&position](const std::pair<int, Cube>& pair) {
						return position == pair.second.position;
					});

				if (it != cubes.end())
				{
					if (it->second.type != Type::Air)
						continue;

					position = Position(x + 1, y, z);
					if (!cubeExists(position))
						cubes.erase(it);
					position = Position(x - 1, y, z);
					if (!cubeExists(position))
						cubes.erase(it);
					position = Position(x, y + 1, z);
					if (!cubeExists(position))
						cubes.erase(it);
					position = Position(x, y - 1, z);
					if (!cubeExists(position))
						cubes.erase(it);
					position = Position(x, y, z + 1);
					if (!cubeExists(position))
						cubes.erase(it);
					position = Position(x, y, z - 1);
					if (!cubeExists(position))
						cubes.erase(it);
				}
			}
		}
	}
}

void Exercise::Part1(std::list<std::string> inputs)
{
	int index = 1;
	for (auto& it : inputs)
	{
		auto split = Utils::split(it, ",");
		Cube cube(index, stoi(split[0]), stoi(split[1]), stoi(split[2]));
		cubes.insert({ index, cube });
		index++;
	}

	int totalSides = 0;
	for (auto& it : cubes)
	{
		int availableSides = 6;
		for (auto& it2 : cubes)
		{
			if (it.second.index != it2.second.index && it.second.isTouching(it2.second))
				availableSides--;
		}
		totalSides += availableSides;
	}

	std::cout << "Free sides: " << totalSides;
}

void Exercise::Part2(std::list<std::string> inputs)
{
	int index = 1;
	xMax = 0;
	yMax = 0;
	zMax = 0;
	for (auto& it : inputs)
	{
		auto split = Utils::split(it, ",");
		Cube cube(index, stoi(split[0]), stoi(split[1]), stoi(split[2]), Type::Solid);
		cubes.insert({ index, cube });

		if (cube.position.x > xMax)
			xMax = cube.position.x;
		if (cube.position.y > yMax)
			yMax = cube.position.y;
		if (cube.position.z > zMax)
			zMax = cube.position.z;

		index++;
	}
	std::cout << "Created " << index << " lava cubes." << std::endl;

	xMax++;
	yMax++;
	zMax++;

	int airCubes = 0;
	for (int x = 0; x <= xMax; x++)
	{
		for (int y = 0; y <= yMax; y++)
		{
			for (int z = 0; z <= zMax; z++)
			{
				Position position(x, y, z);
				auto it = std::find_if(cubes.begin(), cubes.end(),
					[&position](const std::pair<int, Cube>& pair) {
						return pair.second.position == position;
					});
				if (it != cubes.end())
					continue;

				Cube airCube(index, x, y, z, Type::Air);
				index++;
				cubes.insert({ index, airCube });
				airCubes++;
			}
		}
	}
	std::cout << "Created " << airCubes << " air cubes." << std::endl;

	eraseOutsideCubes();

	std::cout << "Erased non-air pockets, remaining air blocks: " << std::count_if(cubes.begin(), cubes.end(),
		[](const std::pair<int, Cube>& pair) {
			return pair.second.type == Type::Air;
		}) << std::endl;

	checkAirPockets();

	std::cout << "Re-checked air pockets, remaining air blocks: " << std::count_if(cubes.begin(), cubes.end(),
		[](const std::pair<int, Cube>& pair) {
			return pair.second.type == Type::Air;
		}) << std::endl;

	int totalSides = 0;
	for (auto& it : cubes)
	{
		if (it.second.type == Type::Air)
			continue;

		int availableSides = 6;
		for (auto& it2 : cubes)
		{
			if (it.second.index != it2.second.index && it.second.isTouching(it2.second))
				availableSides--;
		}
		totalSides += availableSides;
	}

	std::cout << "Free sides: " << totalSides;
}