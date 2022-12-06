#include "../../Utils/Utils.h"
#include "Part1.h"

struct Pair
{
	int begin;
	int end;

	void SetValues(const std::string& input)
	{
		auto values = Utils::split(input, ("-"));
		begin = stoi(values[0]);
		end = stoi(values[1]);
	}

	bool IsContainedBy(const Pair& pair)
	{
		if (pair.begin <= begin && pair.end >= end)
			return true;
		return false;
	}
};

void Part1::Run(std::list<std::string> inputs)
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