#pragma once

struct Valve
{
	std::string name;
	int rate;
	bool opened;

	std::vector<std::string> tunnelOutputs;
	
	std::vector<std::string> visitedBy;
	std::string visitor;

	Valve()
	{
		name = "";
		rate = 0;
		opened = false;
		visitor = "";
	}

	int getSoloTunnelsAmount(std::map<std::string, Valve>& valves)
	{
		if (tunnelOutputs.size() > 1)
			return 0;

		int tunnels = 0;
		Valve* next = this;
		std::vector<std::string> visited;

		while (next->tunnelOutputs.size() <= 2)
		{
			tunnels++;
			visited.push_back(next->name);

			for (auto& it : next->tunnelOutputs)
			{
				auto itFind = std::find(visited.begin(), visited.end(), it);
				if (itFind != visited.end())
					continue;
				next = &valves[it];
			}

			auto itFind = std::find(visited.begin(), visited.end(), next->name);
			if (itFind != visited.end())
				break;
		}
		return tunnels;
	}

	int getStepsFromValve(Valve* other, std::map<std::string, Valve>& valves)
	{
		return getPathFromValve(other, valves).size();
	}

	std::vector<std::string> getPathFromValve(Valve* other, std::map<std::string, Valve>& valves)
	{
		if (other->name == name)
			return {};

		std::vector<std::string> ret;
		for (auto& it : other->tunnelOutputs)
		{
			if (it == name)
			{
				ret.push_back(name);
				return ret;
			}
		}

		for (auto& it : tunnelOutputs)
		{
			for (auto& it2 : other->tunnelOutputs)
			{
				if (it == it2)
				{
					ret.push_back(it2);
					ret.push_back(name);
					return ret;
				}
			}
		}

		std::vector<std::string> finalPath;
		int testCount = 0;
		while (testCount < valves.size())
		{
			std::vector<std::string> path;
			Valve* current = other;
			while (path.size() < valves.size())
			{
				bool foundNewPath = false;
				std::string old = current->name;
				bool isInPath = false;
				for (auto& it : current->tunnelOutputs)
				{
					if (it == current->visitor)
						continue;

					auto visited = std::find_if(valves[it].visitedBy.begin(), valves[it].visitedBy.end(),
						[&current](const std::string& visitor) {
							return visitor == current->name;
						});
					
					if (visited != valves[it].visitedBy.end())
						continue;

					current = &valves[it];

					if(old != current->name)
						current->visitor = old;

					auto inPath = std::find(path.begin(), path.end(), it);
					if (inPath != path.end() || current->name == other->name)
					{
						current->visitedBy.push_back(current->visitor);
						isInPath = true;
						current = other;
						break;
					}
					path.push_back(current->name);
					foundNewPath = true;
					break;
				}

				if (!foundNewPath)
				{
					if(!isInPath)
						current->visitedBy.push_back(current->visitor);
					current = other;
					break;
				}

				if (current->name == name && (finalPath.empty() || path.size() < finalPath.size()))
					finalPath = path;
			}
			path.clear();
			testCount++;
		}

		for (auto& it : valves)
		{
			it.second.visitor = "";
			it.second.visitedBy.clear();
		}

		return finalPath;
	}
};

class Exercise
{
	std::map<std::string, Valve> valves;
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