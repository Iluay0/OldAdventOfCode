#include "../../Utils/Utils.h"
#include "Part1.h"

void Part1::Run(std::list<std::string> inputs)
{
	int mostCalories = 0;
	int curCalories = 0;
	for (auto& it : inputs)
	{
		if (it == "")
		{
			if (curCalories > mostCalories)
				mostCalories = curCalories;
			curCalories = 0;
		}
		else
			curCalories += stoi(it);
	}
	std::cout << "Most Calories carried: " << mostCalories << "\n";
}