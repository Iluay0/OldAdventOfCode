#include "../../Utils/Utils.h"
#include "Exercise.h"

void Exercise::read(std::list<std::string> inputs)
{
	std::regex rgx("Valve (\\w+) has flow rate=([0-9]+); tunnels lead to valves (.+)");
	std::regex rgx2("Valve (\\w+) has flow rate=([0-9]+); tunnel leads to valve (.+)");
	std::smatch match;
	for (auto& it : inputs)
	{
		Valve valve;
		const std::string s = it;
		if (std::regex_search(s.begin(), s.end(), match, rgx))
		{
			valve.name = match[1];
			valve.rate = stoi(match[2]);
			valve.tunnelOutputs = Utils::split(match[3], ", ");
		}
		else if (std::regex_search(s.begin(), s.end(), match, rgx2))
		{
			valve.name = match[1];
			valve.rate = stoi(match[2]);
			valve.tunnelOutputs = Utils::split(match[3], ", ");
		}
		else
			throw;
		valves.insert({ valve.name, valve });
	}
}

void Exercise::Part1(std::list<std::string> inputs)
{
	read(inputs);
	std::string currentLocation = "AA";
	std::set<std::string> openValves;
	std::vector<std::string> currentPath;
	int time = 30;
	int totalPressure = 0;
	for (int i = 1; i <= time; i++)
	{
		std::cout << std::endl << "== Minute " << i << " ==" << std::endl;
		if (openValves.empty())
			std::cout << "No valves are open." << std::endl;
		else
		{
			std::cout << "Valves open:";
			int pressure = 0;
			for (auto& it : openValves)
			{
				std::cout << " " << it;
				pressure += valves[it].rate;
			}
			std::cout << ", pressure: " << pressure << std::endl;
			totalPressure += pressure;
		}

		std::vector<std::pair<std::string, int>> options;

		int currentLocationValue = 0;
		int pathValue = 0;
		for (auto& it : valves)
		{
			if (it.second.rate == 0 || it.second.opened)
				continue;

			int steps = it.second.getStepsFromValve(&valves[currentLocation], valves) + 1;
			if (steps == 1 && it.second.name != currentLocation)
				continue;

			int activeTime = (time - i) - steps;
			int inconvenience = it.second.getSoloTunnelsAmount(valves);
			options.push_back({ it.second.name, it.second.rate * (activeTime - inconvenience) });
			if (it.first == currentLocation)
				currentLocationValue = options.back().second;
			if (!currentPath.empty() && it.first == currentPath.back())
				pathValue = options.back().second;
		}

		if (options.empty())
			continue;

		std::sort(options.begin(), options.end(),
			[](const std::pair<std::string, float>& a, const std::pair<std::string, float>& b) {
				return a.second > b.second;
			});

		if (valves[currentLocation].rate > 0 && !valves[currentLocation].opened && (currentPath.empty() || currentLocationValue > pathValue * 0.75f))
		{
			std::cout << "You open valve " << currentLocation << std::endl;
			valves[currentLocation].opened = true;
			openValves.insert(currentLocation);
			continue;
		}

		if (currentPath.empty())
			currentPath = valves[options.front().first].getPathFromValve(&valves[currentLocation], valves);

		std::cout << "Path: ";
		for (auto& it : currentPath)
			std::cout << " " << it;
		std::cout << std::endl;
		currentLocation = currentPath.front();
		currentPath.erase(currentPath.begin());
		std::cout << "You move to valve " << currentLocation << std::endl;
	}

	std::cout << "Total pressure released: " << totalPressure;
}

void Exercise::Part2(std::list<std::string> inputs)
{
	read(inputs);
	std::string currentLocation = "AA";
	std::string elephantLocation = "AA";
	std::set<std::string> openValves;
	std::vector<std::string> currentPath;
	std::vector<std::string> elephantPath;
	std::string currentGoal = "";
	std::string elephantGoal = "";
	int time = 26;
	int totalPressure = 0;
	for (int i = 1; i <= time; i++)
	{
		std::cout << std::endl << "== Minute " << i << " ==" << std::endl;
		if (openValves.empty())
			std::cout << "No valves are open." << std::endl;
		else
		{
			std::cout << "Valves open:";
			int pressure = 0;
			for (auto& it : openValves)
			{
				std::cout << " " << it;
				pressure += valves[it].rate;
			}
			std::cout << ", pressure: " << pressure << std::endl;
			totalPressure += pressure;
		}

		{
			std::vector<std::pair<std::string, int>> options;

			int currentLocationValue = 0;
			int pathValue = 0;
			for (auto& it : valves)
			{
				if (it.second.rate == 0 || it.second.opened)
					continue;

				if (elephantGoal != "" && it.second.name == elephantGoal)
					continue;

				int steps = it.second.getStepsFromValve(&valves[currentLocation], valves) + 1;
				if (steps == 1 && it.second.name != currentLocation)
					continue;

				int activeTime = (time - i) - steps;
				int inconvenience = it.second.getSoloTunnelsAmount(valves);
				options.push_back({ it.second.name, it.second.rate * (activeTime - inconvenience) });
				if (it.first == currentLocation)
					currentLocationValue = options.back().second;
				if (!currentPath.empty() && it.first == currentPath.back())
					pathValue = options.back().second;
			}

			if (!options.empty())
			{
				std::sort(options.begin(), options.end(),
					[](const std::pair<std::string, float>& a, const std::pair<std::string, float>& b) {
						return a.second > b.second;
					});

				if (valves[currentLocation].rate > 0 && !valves[currentLocation].opened && (currentPath.empty() || currentLocationValue > pathValue * 0.75f))
				{
					std::cout << "You open valve " << currentLocation << std::endl;
					valves[currentLocation].opened = true;
					openValves.insert(currentLocation);
				}
				else
				{
					if (currentPath.empty())
						currentPath = valves[options.front().first].getPathFromValve(&valves[currentLocation], valves);
					currentGoal = currentPath.back();

					currentLocation = currentPath.front();
					currentPath.erase(currentPath.begin());
					std::cout << "You move to valve " << currentLocation << std::endl;
				}
			}
		}

		{
			std::vector<std::pair<std::string, int>> options;

			int currentLocationValue = 0;
			int pathValue = 0;
			for (auto& it : valves)
			{
				if (it.second.rate == 0 || it.second.opened)
					continue;

				if (currentGoal != "" && it.second.name == currentGoal)
					continue;

				int steps = it.second.getStepsFromValve(&valves[elephantLocation], valves) + 1;
				if (steps == 1 && it.second.name != elephantLocation)
					continue;

				int activeTime = (time - i) - steps;
				int inconvenience = it.second.getSoloTunnelsAmount(valves);
				options.push_back({ it.second.name, it.second.rate * (activeTime - inconvenience) });
				if (it.first == elephantLocation)
					currentLocationValue = options.back().second;
				if (!elephantPath.empty() && it.first == elephantPath.back())
					pathValue = options.back().second;
			}

			if (options.empty())
				continue;

			std::sort(options.begin(), options.end(),
				[](const std::pair<std::string, float>& a, const std::pair<std::string, float>& b) {
					return a.second > b.second;
				});

			if (valves[elephantLocation].rate > 0 && !valves[elephantLocation].opened && (elephantPath.empty() || currentLocationValue > pathValue * 0.75f))
			{
				std::cout << "The elephant opens valve " << elephantLocation << std::endl;
				valves[elephantLocation].opened = true;
				openValves.insert(elephantLocation);
				continue;
			}

			if (elephantPath.empty())
				elephantPath = valves[options.front().first].getPathFromValve(&valves[elephantLocation], valves);
			elephantGoal = elephantPath.back();

			elephantLocation = elephantPath.front();
			elephantPath.erase(elephantPath.begin());
			std::cout << "The elephant moves to valve " << elephantLocation << std::endl;
		}
	}

	std::cout << "Total pressure released: " << totalPressure;
}