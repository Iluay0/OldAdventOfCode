#include "../../Utils/Utils.h"
#include "Exercise.h"

void Exercise::read(std::list<std::string> inputs)
{
	for (auto& it : inputs)
	{
		std::regex rgx("Blueprint ([0-9]+): Each ore robot costs ([0-9]+) ore. Each clay robot costs ([0-9]+) ore. Each obsidian robot costs ([0-9]+) ore and ([0-9]+) clay. Each geode robot costs ([0-9]+) ore and ([0-9]+) obsidian.");
		std::smatch match;
		for (auto& it : inputs)
		{
			const std::string s = it;
			if (std::regex_search(s.begin(), s.end(), match, rgx))
			{
				Blueprint blueprint(stoi(match[1]));

				RobotType oreRobot(Material::Ore);
				oreRobot.cost.insert({ Material::Ore, stoi(match[2]) });
				blueprint.robotTypes.insert({ oreRobot.collectType, oreRobot });

				RobotType clayRobot(Material::Clay);
				clayRobot.cost.insert({ Material::Ore, stoi(match[3]) });
				blueprint.robotTypes.insert({ clayRobot.collectType, clayRobot });

				RobotType obsidianRobot(Material::Obsidian);
				obsidianRobot.cost.insert({ Material::Ore, stoi(match[4]) });
				obsidianRobot.cost.insert({ Material::Clay, stoi(match[5]) });
				blueprint.robotTypes.insert({ obsidianRobot.collectType, obsidianRobot });

				RobotType geodeRobot(Material::Geode);
				geodeRobot.cost.insert({ Material::Ore, stoi(match[6]) });
				geodeRobot.cost.insert({ Material::Obsidian, stoi(match[7]) });
				blueprint.robotTypes.insert({ geodeRobot.collectType, geodeRobot });

				blueprints.insert({ blueprint.index, blueprint });
			}
			else
				throw;
		}
	}
}

std::string Exercise::materialToString(const Material& material)
{
	switch (material)
	{
		case Material::Ore:
			return "Ore";
		case Material::Clay:
			return "Clay";
		case Material::Obsidian:
			return "Obsidian";
		case Material::Geode:
			return "Geode";
	}
	return "Unknown";
}

bool Exercise::tryMakeRobot(Blueprint& blueprint, const Material& collectType)
{
	const auto& neededMaterials = blueprint.robotTypes[collectType].cost;

	// Check materials
	for (const auto& it : neededMaterials)
	{
		if (ownedMaterials[it.first] < it.second)
			return false;
	}

	// Craft
	for (const auto& it : neededMaterials)
	{
		ownedMaterials[it.first] -= it.second;
	}
	pendingRobots[collectType]++;
	std::cout << "You create a robot to collect " << materialToString(collectType) << std::endl;
	return true;
}

void Exercise::Part1(std::list<std::string> inputs)
{
	read(inputs);

	int timeLimit = 24;
	for (auto& it : blueprints)
	{
		std::cout << "===== Blueprint " << it.first << " =====" << std::endl;

		ownedRobots = { { Material::Ore, 1 }, { Material::Clay, 0 }, { Material::Obsidian, 0 }, { Material::Geode, 0 }};
		pendingRobots = { { Material::Ore, 0 }, { Material::Clay, 0 }, { Material::Obsidian, 0 }, { Material::Geode, 0 } };
		ownedMaterials = { { Material::Ore, 0 }, { Material::Clay, 0 }, { Material::Obsidian, 0 }, { Material::Geode, 0 } };
		for (int i = 1; i <= timeLimit; i++)
		{
			std::cout << "== Minute " << i << " ==" << std::endl;

			std::map<Material, int> neededResources = {
				{Material::Obsidian, it.second.robotTypes[Material::Geode].cost[Material::Obsidian] / 3},
				{Material::Clay, it.second.robotTypes[Material::Obsidian].cost[Material::Clay] / 3},
				{Material::Ore, (it.second.robotTypes[Material::Ore].cost[Material::Ore] + it.second.robotTypes[Material::Clay].cost[Material::Ore] + it.second.robotTypes[Material::Obsidian].cost[Material::Ore]) / 3}
			};

			if (!tryMakeRobot(it.second, Material::Geode))
			{
				for (auto& it2 : neededResources)
				{
					if (ownedRobots[it2.first] < it2.second)
					{
						if (tryMakeRobot(it.second, it2.first))
							break;
					}
				}
			}

			for (auto& it2 : ownedRobots)
			{
				ownedMaterials[it2.first] += it2.second;

				if(it2.second > 0)
					std::cout << it2.second << " " << materialToString(it2.first) << "-collecting robot collect " << it2.second << " " << materialToString(it2.first) << ", you now have " << ownedMaterials[it2.first] << std::endl;
			}

			for (auto& it2 : pendingRobots)
			{
				ownedRobots[it2.first] += it2.second;
				if (it2.second > 0)
					std::cout << it2.second << " " << materialToString(it2.first) << "-collecting robot is ready, you now have " << ownedRobots[it2.first] << std::endl;
				it2.second = 0;
			}

			std::cout << std::endl;
		}

		std::cout << std::endl << std::endl;
	}
}

void Exercise::Part2(std::list<std::string> inputs)
{

}