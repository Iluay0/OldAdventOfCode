#include "../../Utils/Utils.h"
#include "Part2.h"

#define NUMBER_OF_DAYS 256
#define OLD_FISH_TIMER 6
#define NEW_FISH_TIMER 8

struct LanternFishType
{
	__int64 amount;
	int daysForSpawn;

	LanternFishType()
	{
		amount = 0;
		daysForSpawn = NEW_FISH_TIMER;
	}
};

void Part2::Run(std::list<std::string> inputs)
{
	std::vector<LanternFishType> lanternFishies;
	for (int i = 0; i <= NEW_FISH_TIMER + 1; i++)
	{
		LanternFishType lanternFishType;
		lanternFishType.amount = 0;
		lanternFishType.daysForSpawn = i;
		lanternFishies.push_back(lanternFishType);
	}

	for (auto& it : inputs)
	{
		auto startFishies = Utils::split(it, ',');
		for (auto& it2 : startFishies)
		{
			auto it = std::find_if(lanternFishies.begin(), lanternFishies.end(),
				[&it2](const LanternFishType& lanternFishType)
				{
					return lanternFishType.daysForSpawn == stoi(it2);
				});

			if (it != lanternFishies.end())
				it->amount++;
		}
	}

	for (int i = 1; i <= NUMBER_OF_DAYS; i++)
	{
		for (int j = 0; j < lanternFishies.size(); j++)
		{
			if (lanternFishies[j].daysForSpawn == 0)
			{
				lanternFishies[j].daysForSpawn = OLD_FISH_TIMER;

				auto it = std::find_if(lanternFishies.begin(), lanternFishies.end(),
					[](const LanternFishType& lanternFishType)
					{
						return lanternFishType.daysForSpawn == NEW_FISH_TIMER + 1;
					});
				if (it != lanternFishies.end())
					it->amount += lanternFishies[j].amount;
			}
			else
			{
				if (lanternFishies[j].daysForSpawn > OLD_FISH_TIMER)
				{
					int daysForSpawn = lanternFishies[j].daysForSpawn;
					auto it = std::find_if(lanternFishies.begin(), lanternFishies.end(),
						[&daysForSpawn](const LanternFishType& lanternFishType)
						{
							return lanternFishType.daysForSpawn == daysForSpawn - 1;
						});
					if (it != lanternFishies.end())
						it->amount += lanternFishies[j].amount;
					lanternFishies[j].amount = 0;
				}
				else
					lanternFishies[j].daysForSpawn--;
			}
		}
		std::cout << "After " << i << "days: ";
		__int64 totalAmount = 0;
		for (auto& it : lanternFishies)
			totalAmount += it.amount;

		std::cout << totalAmount << "\n";
	}

	__int64 totalAmount = 0;
	for (auto& it : lanternFishies)
		totalAmount += it.amount;

	std::cout << totalAmount;
}