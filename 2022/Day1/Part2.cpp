#include "../../Utils/Utils.h"
#include "Part2.h"

void Part2::Run(std::list<std::string> inputs)
{
	std::list<int> mostCalories = { 0, 0, 0 };
	int curCalories = 0;
	for (auto& it : inputs)
	{
		if (it == "")
		{
			for (auto it = mostCalories.begin(); it != mostCalories.end(); it++)
			{
				if (curCalories > *it)
				{
					mostCalories.insert(it, curCalories);
					break;
				}
			}
			curCalories = 0;
		}
		else
			curCalories += stoi(it);

		if (mostCalories.size() > 3)
			mostCalories.pop_back();
	}

	int count = 1;
	for (auto& it : mostCalories)
	{
		std::cout << "Calories of top " << count << " : " << it << "\n";
		count++;
	}

	std::cout << "Total: " << Utils::listSum(mostCalories);
}