#include "../../Utils/Utils.h"
#include "Part2.h"

void Part2::Run(std::list<std::string> inputs)
{
	int curVal = 0;

	int amount = 0;

	std::list<int> prevVals;
	std::list<int> curVals;

	for (auto& it : inputs)
	{
		curVal = stoi(it);
		curVals.push_back(curVal);

		while (curVals.size() > 3)
			curVals.pop_front();

		if (prevVals.size() == 3 && curVals.size() == 3 && Utils::listSum(curVals) > Utils::listSum(prevVals))
			amount++;

		prevVals.push_back(curVal);

		while (prevVals.size() > 3)
			prevVals.pop_front();
	}

	std::cout << amount << "\n";
}