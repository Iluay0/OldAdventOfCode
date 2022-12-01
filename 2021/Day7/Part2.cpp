#include "../../Utils/Utils.h"
#include "Part2.h"

void Part2::Run(std::list<std::string> inputs)
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

	int mean = 0;
	for (auto& it : startPositions)
	{
		mean += it;
	}
	mean /= startPositions.size();

	std::cout << "Going to position " << mean << "\n";

	int fuel = 0;
	for (auto& it : startPositions)
	{
		int move = abs(mean - it);
		fuel += (int)(move * (move + 1) / 2);
	}

	std::cout << "Fuel consumed: " << fuel << "\n";
}