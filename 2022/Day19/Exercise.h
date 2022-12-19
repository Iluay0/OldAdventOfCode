#pragma once

enum Material
{
	Ore = 0,
	Clay,
	Obsidian,
	Geode
};

struct RobotType
{
	Material collectType;
	std::map<Material, std::uint8_t> cost;

	RobotType()
	{
		this->collectType = Material::Ore;
	}

	RobotType(Material collectType)
	{
		this->collectType = collectType;
	}
};

struct Blueprint
{
	int index;
	std::map<Material, RobotType> robotTypes;

	Blueprint()
	{
		this->index = -1;
	}

	Blueprint(int index)
	{
		this->index = index;
	}
};

class Exercise
{
	std::map<Material, int> ownedRobots;
	std::map<Material, int> ownedMaterials;
	std::map<Material, int> pendingRobots;

	std::map<int, Blueprint> blueprints;

	std::string materialToString(const Material& material);
	bool tryMakeRobot(Blueprint& blueprint, const Material& collectType);
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