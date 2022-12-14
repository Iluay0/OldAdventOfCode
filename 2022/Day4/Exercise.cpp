#include "../../Utils/Utils.h"
#include "Exercise.h"

void Exercise::Part1(std::list<std::string> inputs)
{
	int amount = 0;
	for (auto& it : inputs)
	{
		auto pairs = Utils::split(it, (","));
		Pair pairOne;
		pairOne.SetValues(pairs[0]);
		Pair pairTwo;
		pairTwo.SetValues(pairs[1]);

		if (pairTwo.IsContainedBy(pairOne) || pairOne.IsContainedBy(pairTwo))
			amount++;
	}
	std::cout << amount;
}

void Exercise::Part2(std::list<std::string> inputs)
{
	int amount = 0;
	for (auto& it : inputs)
	{
		auto pairs = Utils::split(it, (","));
		Pair pairOne;
		pairOne.SetValues(pairs[0]);
		Pair pairTwo;
		pairTwo.SetValues(pairs[1]);

		if (pairOne.IsOverlappingWith(pairTwo))
			amount++;
	}
	std::cout << amount;
}