#include "../../Utils/Utils.h"
#include "Part1.h"

void Part1::Run(std::list<std::string> inputs)
{
	int curVal = 0;
	int prevVal = 0;

	int amount = 0;
	for (auto& it : inputs)
	{
		curVal = stoi(it);

		if (prevVal != 0 && curVal > prevVal)
			amount++;

		prevVal = curVal;
	}

	std::cout << amount << "\n";
}