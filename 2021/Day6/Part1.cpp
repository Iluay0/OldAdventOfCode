#include "../../Utils/Utils.h"
#include "Part1.h"

#define NUMBER_OF_DAYS 80
#define OLD_FISH_TIMER 6
#define NEW_FISH_TIMER 8

void Part1::Run(std::list<std::string> inputs)
{
	std::vector<int> lanternFishies;
	for (auto& it : inputs)
	{
		auto startFishies = Utils::split(it, ',');
		for (auto& it2 : startFishies)
		{
			lanternFishies.push_back(stoi(it2));
		}
	}

	for (int i = 1; i <= NUMBER_OF_DAYS; i++)
	{
		for (int j = 0; j < lanternFishies.size(); j++)
		{
			if (lanternFishies[j] == 0)
			{
				lanternFishies[j] = OLD_FISH_TIMER;
				lanternFishies.push_back(NEW_FISH_TIMER + 1);
			}
			else
				lanternFishies[j]--;
		}
		/*
		std::cout << "After " << i << "days: ";
		for (int j = 0; j < lanternFishies.size(); j++)
		{
			std::cout << lanternFishies[j] << ",";
		}
		std::cout << "\n";
		*/
	}

	std::cout << lanternFishies.size();
}