#include "../../Utils/Utils.h"
#include "Part1.h"

void Part1::Run(std::list<std::string> inputs)
{
	std::vector<int> startPositions;
	for (auto& it : inputs)
	{
		auto positions = Utils::split(it, ',');
		for (auto& it2 : positions)
		{
			startPositions.push_back(stoi(it2));
		}
	}

	std::sort(startPositions.begin(), startPositions.end());
	int median = startPositions[startPositions.size() / 2];

	std::cout << "Going to position " << median << "\n";

	int fuel = 0;
	for (auto& it : startPositions)
	{
		fuel += abs(median - it);
	}

	std::cout << "Fuel consumed: " << fuel << "\n";
}